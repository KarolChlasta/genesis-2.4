/* Version EDS22d 98/08/14, Erik De Schutter, Caltech & BBF-UIA 4/94-8/98 */
/* Original version by Upi Bhalla, Caltech 1991 */

/*
** EDS22j revison: HC BBF-UIA 00/03/13
** default value of ->msgcompts[i] dependent on ->computeIm field
**
** EDS22c revison: EDS BBF-UIA 97/11/28-98/08/14
** Extensively edited original h_init.c code
** Made symmetric compartments work
** Deleted use of values array
** Improved error messages
**
*/

#include "hines_ext.h"

/* GENESIS 2.5 (2026-07-25): pointer->index lookup for compts[], used in
** h_init() to find the array index of an Element* (an AXIAL message's
** source, or a parent) without an O(ncompts) linear scan per compartment.
** Plain linear-probing hash over a power-of-two table. */
typedef struct { Element *key; int idx; } CidxEntry;

static int CidxLookup(cidx, cidx_size, key)
CidxEntry	*cidx;
int		cidx_size;
Element		*key;
{
int hi;

    hi = (int)(((unsigned long)key >> 4) & (cidx_size-1));
    while (cidx[hi].key != NULL) {
	if (cidx[hi].key == key)
	    return cidx[hi].idx;
	hi = (hi+1) & (cidx_size-1);
    }
    return -1;
}

int h_init(hsolve)
	Hsolve	*hsolve;
{
	ElementList *list;
	int 	ncompts;
	Comp	**compts = NULL;
	Comp	*compt;
	int 	i,j,k,n,f;
	MsgIn	*msgin;
	int	hnumcount;
	int	*parents,**kids,*nkids,*elmnum,*hnum;
	int	temp;
	int	chanmode,symflag;
	Element *elm;
	Element *saveelm;
	char*   oname;
	int	hhas_msg_toelm();

	double		Ra1;
	double 		Ra_sum,Ra_sum2;

	chanmode=hsolve->chanmode;
	if (hsolve->readflag < HREAD_T) { /* standard initialization */
	    if (!(hsolve->path)) {
		Error();
		printf(" during SETUP of %s: no path defined.\n",Pathname(hsolve));
		return(ERR);
	    }
	    /* Allow path relative to hsolve to work always */
	    saveelm = WorkingElement();
	    SetWorkingElement(hsolve);
	    list = WildcardGetElement(hsolve->path,0);
	    SetWorkingElement(saveelm);

	    hsolve->ncompts = ncompts = list->nelements;
	    hsolve->compts = list->element;
	    compts = (Comp **)hsolve->compts;
	} else {
	    ncompts=hsolve->ncompts;
	}
	if (ncompts==0) {
	    elm=WorkingElement();
	    Error();
	    printf(" during SETUP of %s: empty path.\n",Pathname(hsolve));
	    return(ERR);
	}
	hsolve->parents = parents = (int *)calloc(ncompts, sizeof(int));
	hsolve->nkids = nkids = (int *)calloc(ncompts, sizeof(int));
	hsolve->kids = kids = (int **)calloc(ncompts, sizeof(int *));
	hsolve->hnum = hnum = (int *)calloc(ncompts,sizeof(int));
	hsolve->elmnum = elmnum = (int *)calloc(ncompts,sizeof(int));
	if (chanmode<2)
	    hsolve->msgcompts = (short *)calloc(ncompts,sizeof(short));
	hsolve->outinfo = NULL;

	if (hsolve->readflag==HREAD_T) { /* called by readsolve */
	    /*
	    if (init_hparents(hsolve))
		    return(ERR);
	    */
	}
	/* Determine if symmetric or not */
	compt = compts[0];
	oname = BaseObject(compt)->name;
	if (strcmp(oname,"symcompartment") == 0) {
	    symflag=1;
	} else if (strcmp(oname,"compartment") == 0) {
	    symflag=0;
	} else {
	    Error();
	    printf(" during SETUP of %s: type '%s' not supported as path.\n",Pathname(hsolve),oname);
	    return(ERR);
	}
	hsolve->symflag=symflag;
	/* build the compts[]-index lookup once, up front (see CidxLookup):
	** avoids an O(ncompts) linear scan per compartment below to find
	** which index an AXIAL message's source element corresponds to
	** (O(ncompts^2) total otherwise -- the dominant hsolve SETUP cost
	** once ncompts reaches the hundreds of thousands, e.g. many small
	** neurons sharing one hsolve). Scope covers the whole loop below;
	** freed right after it. */
	{
	CidxEntry	*cidx;
	int		cidx_size, ci, hi;

	    cidx_size = 1;
	    while (cidx_size < ncompts*2) cidx_size *= 2;
	    cidx = (CidxEntry *)calloc(cidx_size, sizeof(CidxEntry));
	    for (ci=0; ci<ncompts; ci++) {
		Element *key = (Element *)compts[ci];
		hi = (int)(((unsigned long)key >> 4) & (cidx_size-1));
		while (cidx[hi].key != NULL) hi = (hi+1) & (cidx_size-1);
		cidx[hi].key = key;
		cidx[hi].idx = ci;
	    }
	/* AXIALs go from parent to kid compts */
	for (i=0;i<ncompts;i++){
	    compt = compts[i];
	    oname = BaseObject(compt)->name;
	    if ((!symflag && (strcmp(oname,"compartment") != 0)) ||
		(symflag && (strcmp(oname,"symcompartment") != 0))) {
		Error();
		printf(" during SETUP of %s: %s is not not same type of compartment as the others.\n",Pathname(hsolve),Pathname(compt));
		return(ERR);
	    }
	    /* disable element to prevent it from doing anything. */
	    HsolveBlock(compt);
	    parents[i] = -1;
	    if (chanmode<2)
	    {
		if (!hsolve->computeIm)
		{
		    hsolve->msgcompts[i] = 0;
		}
		else
		{
		    hsolve->msgcompts[i] = 1;
		}
	    }

	    Ra_sum = 0.0;
	    Ra_sum2 = 0.0;

	    /* look for parent compts */
	    MSGLOOP(compt, msgin) {
	    case AXIAL: /* 2 : is same as CONNECTHEAD */
		if (Strindex(BaseObject(msgin->src)->name,"compartment")>=0)
		{
		    j = CidxLookup(cidx, cidx_size, msgin->src);
		    if (j != -1)
		    {
			/* the jth elment is a parent of the ith element */
			if (parents[i] != -1)
			{
			    Error();
			    printf
				(" during SETUP of %s: multiple parents for compartment '%s'.\n",
				 Pathname(hsolve),
				 Pathname(compt));
			    return(ERR);
			}
			parents[i] = j;
			nkids[j] += 1;
		    }
		}

		if (symflag)
		{
		    Ra1 = MSGVALUE(msgin,0);
		    if (Ra1 <= 0.0)
		    {
			ErrorMessage
			    ("hsolve",
			     "Incoming Ra invalid.",
			     compt);
		    }
		    Ra_sum2 += compt->Ra/Ra1;
		}
		break;

	    case RAXIAL:  /* 1 : resistive axial */
		if (symflag)
		{
		    Ra1 = MSGVALUE(msgin,0);
		    if (Ra1 <= 0.0)
		    {
			ErrorMessage
			    ("hsolve",
			     "Incoming Ra invalid.",
			     compt);
		    }
		    Ra_sum += compt->Ra/Ra1;
		}
		break;
	    case CONNECTCROSS: /* 5 : branch of symcompartments */
		if (symflag)
		{
		    Ra1 = MSGVALUE(msgin,0);
		    if (Ra1 <= 0.0)
		    {
			ErrorMessage
			    ("hsolve",
			     "Incoming Ra invalid.",
			     compt);
		    }
		    Ra_sum2 += compt->Ra/Ra1;
		}
		break;
	    case INJECT:
	    case EREST:
		if (chanmode<2) {
		    /* we need to update internal fields in compartment */
		    (hsolve->msgcompts[i])++;
		}
		break;

	    default:
		break;
	    }

	    if (symflag)
	    {
		((Ncomp *)compt)->coeff = (1 + Ra_sum)/2.0;
		((Ncomp *)compt)->coeff2 = (1 + Ra_sum2)/2.0;
	    }
	}
	free(cidx);
	}
	/* Fill in indices for kids: one O(ncompts) pass instead of an
	** O(ncompts) scan per parent (O(ncompts^2) total) -- nkids[] is
	** already known from the loop above, so each kids[i] can be
	** allocated up front and filled via a per-parent fill cursor. */
	{
	int *kidcursor = (int *)calloc(ncompts, sizeof(int));

	    for (i=0;i<ncompts;i++){
		if (nkids[i] == 0) {
		    kids[i] = NULL; /* a terminal branch */
		} else {
		    kids[i]=(int *)calloc(nkids[i],sizeof(int));
		}
	    }
	    for (j=0;j<ncompts;j++) {
		if (parents[j] != -1) {
		    k = parents[j];
		    kids[k][kidcursor[k]++] = j;
		}
	    }
	    free(kidcursor);
	}

	/* assign Hines numbers across all roots (supports multiple disconnected trees) */
	hnumcount = ncompts-1;
	for (i=0;i<ncompts;i++){
	    if (parents[i] == -1) {
		do_hnum(hsolve,i,&hnumcount,elmnum);
	    }
	}
	/* sort the kids by Hines number (useful for h_funcs_init ) */
	for (i=0;i<ncompts;i++){
	    j=elmnum[i];
	    n=nkids[j];
	    /* do bubble sort */
	    f=1;
	    while (f) {
		f=0;
		for(k=1;k<n;k++) {
		    if (hnum[kids[j][k-1]]>hnum[kids[j][k]]) {
			temp = kids[j][k-1];
			kids[j][k-1] = kids[j][k];
			kids[j][k] = temp;
			f=1;
		    }
		}
	    }
	}
	return(0);
}

int h2_init(hsolve)
	Hsolve	*hsolve;
{
	int ncompts;

	ncompts=hsolve->ncompts;
	hsolve->vm = (double *) calloc(ncompts,sizeof(double));
	if (hsolve->numnodes==0) {	/* uniprocessor mode */
	    /* diag also stored in results */
	    hsolve->results=(double *)calloc(2*ncompts,sizeof(double));
	    hsolve->vmlast=hsolve->vm + hsolve->ncompts - 1;  /* pointer to end of vm array */
	    if (hsolve->chanmode<2)
		hsolve->diagonals=(double *)calloc(ncompts,sizeof(double));
	}
	return(0);
}

/* Doing hines numbering */
int do_hnum(hsolve,comptno,hnum,elmnum)
	Hsolve	*hsolve;
	int	comptno;
	int	*hnum;
	int	*elmnum;
{
	int i;
	int kidno;

	hsolve->hnum[comptno]= *hnum;
	elmnum[*hnum]=comptno;
	*hnum -= 1;
	for(i=0;i<hsolve->nkids[comptno];i++) {
	    /* Numbering kids of this elm which have no kids of their own */
	    kidno = hsolve->kids[comptno][i];
	    if (hsolve->nkids[kidno]==0) {
		hsolve->hnum[kidno] = *hnum;
		elmnum[*hnum]=kidno;
		*hnum -= 1;
	    }
	}
	for(i=0;i<hsolve->nkids[comptno];i++) {
	    /* Numbering kids of this elm which do have kids of their own */
	    kidno = hsolve->kids[comptno][i];
	    if (hsolve->nkids[kidno]>0) {
		do_hnum(hsolve,kidno,hnum,elmnum);
	    }
	}
}

/* This routine sets up the diagonals (or results if chanmode>1), funcs and
**  ravals arrays.  It does this in two passes : first, it finds the number
**  of entries in the funcs and ravals arrays, second (during RESET) it
**  fills them up.
** funcs: array with instruction codes for fast solution of the
**  sparse matrix. Is created only if comptmode>0 (default)
** diagonals: array with the constant part of the diagonal values.
** ravals: contains the off-diagonal parameters in order of funcs access.  Is
**  allways created.  For symmetric compartments it will be changed during
**  the simulation.
** If chanmode >1: stores diag elements in results array
** The code contains many controls which produce "Bug" errors if triggered.
**  This was done to protect agains untested complex situtations (e.g. many
**  children). */
int h_funcs_init(hsolve)
	Hsolve	*hsolve;
{
	int     i,j,k,l = 0,m,n;
	int	ncompts=hsolve->ncompts;
	int     symflag=hsolve->symflag;
	int	*elmnum=hsolve->elmnum;
	int	*hnum=hsolve->hnum;
	int	*parents=hsolve->parents;
	int	*nkids=hsolve->nkids;
	int	**kids=hsolve->kids;
	int	*compchips=hsolve->compchips;
	double  *diagonals=hsolve->diagonals;
	double  *chip=hsolve->chip;
	double  *results=hsolve->results;
	int	parentno,nkid,row,row2,maxkids=1,self = 0;
	int     comptindex;
	int     justcount=1,skipdiag=0,hassiblefts=0,found;
	int     nfuncs=0,nravals=0;
	int	*funcs = NULL,**ravptr = NULL;
	double  *ravals = NULL,*coeffs,*diagterms;
	/* GENESIS 2.5 GPU-solve prep (2026-07-25): temporary map from a root
	** compartment's index to its assigned tree slot (0..n_trees-1), so the
	** backward pass (which visits roots in a different order than the
	** forward pass discovered them) can write bwd_seg_start[] into the
	** SAME slot as the matching fwd_seg_start[] entry. Local to this
	** function; not persisted on Hsolve. See GPU_HINES_SOLVE_DESIGN.md. */
	int	*root_to_tree_idx = NULL;
	double  temp,dt,Cm,Ra;
	Comp	**compts=(Comp **)hsolve->compts;
	Comp	*compt,*parent = NULL,*link,*link2;
	int	hhas_msg_toelm();

	coeffs=NULL;
	diagterms=NULL;
	if (BaseObject(hsolve)->method == CRANK_INT)
	    dt = hsolve->dt/2.0;
	else /* BEULER by default */
	    dt = hsolve->dt;

        if (hsolve->nfuncs == 0) {
	    if (symflag) {
		/* ravptr orders: 0:                   right parent off-diagonal
		**                1 - maxkid:          left kid off-diagonals
		**                maxkid+1 - 2*maxkid: all sib off-diagonals
		**  All ordered as in kids
		**  Initialized to -1, then set to a funcs index and cleared (0)
		**  or used as storage for a ravals index (<-1).
		*/
		/* create pointer array for ravals */
		for (i=0;i<ncompts;i++) {
		    nkid=nkids[i];
		    if (nkid>maxkids) maxkids=nkid;
		}
		hsolve->ravptr=ravptr=(int **)calloc(ncompts,sizeof(int *));
		n=maxkids*2+1;
		for (i=0;i<ncompts;i++) {
		    ravptr[i]=(int *)calloc(n,sizeof(int));
		    for (j=0;j<n;j++) ravptr[i][j]=-1;
		}
	    }
	} else {
            justcount = 0;
            if (hsolve->funcs)  {
		funcs=hsolve->funcs;
            } else {
                hsolve->funcs=funcs=(int *)calloc(hsolve->nfuncs,sizeof(int));
	    }
	    /* GENESIS 2.5 GPU-solve prep: allocate per-tree segment arrays
	    ** (safe upper bound ncompts: worst case every compartment is its
	    ** own disconnected tree) and the local root->tree-index map. */
	    if (!hsolve->fwd_seg_start) hsolve->fwd_seg_start=(int *)calloc(ncompts,sizeof(int));
	    if (!hsolve->bwd_seg_start) hsolve->bwd_seg_start=(int *)calloc(ncompts,sizeof(int));
	    if (!hsolve->fwd_root_row) hsolve->fwd_root_row=(int *)calloc(ncompts,sizeof(int));
	    if (!hsolve->fwd_raval_start) hsolve->fwd_raval_start=(int *)calloc(ncompts,sizeof(int));
	    if (!hsolve->bwd_raval_start) hsolve->bwd_raval_start=(int *)calloc(ncompts,sizeof(int));
	    for (i=0;i<ncompts;i++) hsolve->bwd_seg_start[i] = -1; /* raw marker, fixed up after the backward loop below (see fixup block) -- never left as -1 in the final struct */
	    hsolve->n_trees = 0;
	    root_to_tree_idx=(int *)calloc(ncompts,sizeof(int));
	    for (i=0;i<ncompts;i++) root_to_tree_idx[i] = -1;
	    if (hsolve->ravals) {
		ravals=hsolve->ravals;
	    } else {
                if (hsolve->nravals) hsolve->ravals=ravals=(double *)calloc(hsolve->nravals,sizeof(double));
            }
	    /* create temporary storage for diagterms */
	    diagterms=(double *)calloc(ncompts,sizeof(double));
	    /* if symmetric compute the coefficients for the Ra values */
	    if (symflag) {
		ravptr=hsolve->ravptr;
		for (i=0;i<ncompts;i++) ravptr[i][0]=-1;  /* clear again */
		/* create temporary storage */
		coeffs=(double *)calloc(ncompts*2,sizeof(double));
		for (i=0;i<ncompts;i++) {
		    comptindex=elmnum[i];
		    compt=compts[comptindex];
		    Ra=compt->Ra;
		    /* coeffs for head Ra */
		    temp=0.0;
		    parentno=parents[comptindex];
		    if (parentno>=0) {
			temp=Ra/compts[parentno]->Ra;
			for (j=0;j<nkids[parentno];j++) {
			    k=kids[parentno][j];
			    if (k!=comptindex) temp+=Ra/compts[k]->Ra;
			}
		    }
		    coeffs[i*2]=(1.0 + temp)/2.0;
		    /* coeff for tail Ra */
		    temp=0.0;
		    nkid=nkids[comptindex];
		    if (nkid>maxkids) maxkids=nkid;
		    for (j=0;j<nkid;j++) {
			k=kids[comptindex][j];
			temp+=Ra/compts[k]->Ra;
		    }
		    coeffs[i*2+1]=(1.0 + temp)/2.0;
		}
	    }
        }

	/* Looping over all rows, doing forward substitution:
	**   we remove the lower left triangle of the matrix
	*/
/* OPTIMIZATION: do all COPY_ARRAYs in a separate loop first */
	/* GENESIS 2.5 GPU-solve prep: track where each tree's OWN opcode range
	** actually BEGINS. IMPORTANT CORRECTION (found empirically 2026-07-25
	** via the CPU-side per-tree validator below hitting real numeric
	** mismatches -- an earlier version of this comment/code wrongly
	** assumed nfuncs at root-detection time (parentno==-1) marked a
	** tree's START; it actually marks very near a tree's END, since
	** "children before parents" postorder means a tree's root -- where
	** parentno==-1 fires -- is the LAST row of that tree to be processed,
	** not the first. A tree's non-root rows (its leaf through its root's
	** own child) all emit their opcodes EARLIER, before its root is ever
	** reached. fwd_tree_start_pos/fwd_tree_start_ravals capture the TRUE
	** start instead: whatever nfuncs/nravals were the moment the row
	** right after the PREVIOUS tree's root began (tracked via
	** prev_was_root, checked at the top of each iteration, before this
	** iteration's own opcodes are emitted). */
	{
	int fwd_tree_start_pos = 0;
	int fwd_tree_start_ravals = 0;
	int prev_was_root = 1;	/* row i=0 always starts a (the first) tree */
	for (i=0;i<ncompts;i++) {
	    comptindex=elmnum[i]; /* i is the hnum of the elm */
	    compt=compts[comptindex];
	    Cm=compt->Cm;
	    if (!justcount) diagterms[i]=1.0 + dt/(Cm*compt->Rm);

	    if (!justcount && prev_was_root) {
		fwd_tree_start_pos = nfuncs;
		fwd_tree_start_ravals = nravals;
		prev_was_root = 0;
	    }

	    /* Start eliminating the PRECEDING ROWS */
	    parentno=parents[comptindex];
	if (!justcount && parentno == -1) {
		/* GENESIS 2.5 GPU-solve prep: record this tree's forward-pass
		** segment start (the TRUE start captured above, not this
		** root row's own position) and remember its slot for the
		** backward pass. fwd_root_row/fwd_raval_start: see
		** hines_struct.h kernel-entry protocol comment -- results[]/
		** vm[] seed point and *ravals++ cursor start for a
		** standalone GPU work-item. */
		hsolve->fwd_seg_start[hsolve->n_trees] = fwd_tree_start_pos;
		hsolve->fwd_root_row[hsolve->n_trees] = i;
		hsolve->fwd_raval_start[hsolve->n_trees] = fwd_tree_start_ravals;
		root_to_tree_idx[comptindex] = hsolve->n_trees;
		hsolve->n_trees++;
		prev_was_root = 1;	/* next iteration (if any) starts a new tree */
		if (getenv("GENESIS_DUMP_FUNCS")) {
		    fprintf(stderr, "FUNCS_DUMP: FWD_ROOT i=%d comptindex=%d nfuncs=%d nravals=%d tree=%d\n",
			    i, comptindex, nfuncs, nravals, hsolve->n_trees-1);
		}
	}
	    if (parentno>-1)
	    {
		parent=compts[parentno];
	    }
	    nkid=nkids[comptindex];
	    if (!justcount && symflag) {
		for (l=nkid+1;l<=maxkids;l++) ravptr[i][l]=0; /* not used */
	    }

	    /* Do children first */
	    /* get diagonal and result for this row:
	    **   code to execute: store previous resultvalue and diavalue
	    **               and: resultvalue=results[i];
	    **               and: diavalue = diagonal[i];
	    */
	    hassiblefts=0;
	    if (symflag) {
	      if (parentno>-1) {
		/* find our own sib number */
		n=nkids[parentno];
		for (j=0; j<n; j++) {
		    if (kids[parentno][j]==comptindex) {
			self=j;
			break;
		    }
		}
		if (n && (j==n)) {
		    printf("Error in %s: Bug #0 in hines_init %d %d.\n",hsolve->name,i,j);
		    return(ERR);
		}
		/* copy parent right-off diagonal this row if it will change:
		**  if it has siblings and it is not the first one */
		if (n>1) {	/* has sibs */
		    if (self>0) {	/* is not first sib */
			if (justcount) {
			    nfuncs+=2;
			    nravals++;
			} else {
			    funcs[nfuncs++]=COPY_ARRAY;
			    ravptr[i][0]=nfuncs;
			    funcs[nfuncs++]=-1;	/* mark as unresolved */
/* test2.analysis: store p4 on row 4 for row 5 */
/* test3.analysis: store P8 on row 8 for row 14 */
/* test3.analysis: store q13 on row 13 for row 14 */
			    /* kid: head connection to parent */
			    temp=-dt/(Cm*parent->Ra*coeffs[i*2]);
			    ravals[nravals++]=temp;
			    diagterms[i]-=temp;
			    hassiblefts=1;
			}
		    }
		} else {
		    if (!justcount) ravptr[i][0]=0;	/* not used */
		}
		if (i==0) {	/* not much done on first row... */
		    /* this code is needed for the control functions only */
		    if (!justcount) {	/* clear unused and sib indices*/
			ravptr[0][maxkids+1]=0;
			for (j=maxkids+n+1;j<=maxkids*2;j++) ravptr[0][j]=0;
		    }
		    continue;
		}
	      } else {
		if (!justcount) ravptr[i][0]=0;	/* not used */
	      }
	    }
	    if (skipdiag) {
		skipdiag=0;
/*  OPTIMIZE FOR DOUBLE SKIP */
	    } else if (nkid || hassiblefts || parentno == -1) {
		/* parentno==-1: this row is itself a disconnected root (no
		** axial parent), e.g. one of several independent single-
		** compartment cells sharing one hsolve. It can never be
		** paired with a following row via the SKIP_DIAG "unbranched
		** cable" optimization below (that pairing assumes a real
		** parent eventually absorbs it), so force the plain 1-row
		** SET_DIAG advance instead. Using SKIP_DIAG here would
		** over-advance resultvalue past the end of results[] when
		** this happens to be the last row (the implicit "soma"),
		** corrupting that row's voltage update. */
		if (i>1) {	/* first SET_DIAG always done */
		    if (justcount) {
			nfuncs++;
		    } else {
			funcs[nfuncs++]=SET_DIAG;
		    }
		}
	    } else {	/* compt is end of unbranched cable without
			**  sib left-off diagonals */
		if (i>1) {	/* first SET_DIAG always done */
		    if (justcount) {
			nfuncs++;
		    } else {
			funcs[nfuncs++]=SKIP_DIAG;
		    }
		    skipdiag=1;
		}
	    }
	    for (j=0; j<nkid; j++) {
		k=kids[comptindex][j];
		link=compts[k];
		row=hnum[k];	/* convert to hines number */
		/* calculate scaling factor and eliminate left off-diag:
		**   code to execute: temp = ravals[n++]/diag[row];
		**               and: diag[i] -= ravals[n++]*temp;
		**               and: results[i] -= results[row]*temp;
		**   with ravals[n++] the left off-diagonal for row
		*/
		if (justcount){
		    nfuncs+=2;			/* FORWARD_ELIM */
		    nravals+=2;
		    if (symflag) {
			ravptr[row][0]=1;/* we need to know this exists later */
			nfuncs+=2*(nkid-1);	/* COPY_ARRAY */
			nravals+=nkid-1;
			nfuncs+=3*(nkid-j-1);	/* SIBARRAY_ELIM */
		    }
		} else {
/* POSSIBLE OPTIMIZATION: IN UNBRANCHED CABLE ROW = i - 1 */
		    funcs[nfuncs++]=FORWARD_ELIM;
		    funcs[nfuncs++]=2*row;
		    if (symflag) { /* symmetric elements */
/* test2.analysis: do row 5 */
/* test3.analysis: do row 14 */
			/* compute ravals for temp: left off-diag on row i
			**  parent: tail connection to kid */
			if (j==0) { /* first one never changes */
/* test2.analysis: eliminate P5, contributed by row 2 */
/* test3.analysis: eliminate Q14, contributed by row 2 */
			    temp=-dt/(Cm*link->Ra*coeffs[i*2+1]);
			    ravals[nravals++]=temp;
			    diagterms[i]-=temp;
			} else {   /* has changed: check if ptr correct! */
/* test2.analysis: eliminate p5', contributed by row 3 */
/* test3.analysis: eliminate P14', contributed by row 8 */
/* test3.analysis: eliminate q14", contributed by row 13 */
			    m=ravptr[i][j+1];
			    if ((m<=0)||(funcs[m]!=-1)) {
				printf("Error in %s: Bug #1 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    funcs[m]=nravals;	/* index is now resolved */
			    found=0;
			    for (l=m; l<nfuncs; l++) {
				/* resolve copies of index also */
				if (funcs[l]==-m) {
				    funcs[l]=nravals;
				    found=1;
				}
			    }
			    if (found==0) {
				printf("Error in %s: Bug #-1 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    nravals++;	/* computed during simulation */
			}
			ravptr[i][j+1]=0;	/* should be done */
			/* compute ravals for diag[i]: right off-diag on row row
			**  kid: head connection to parent */
/* test2.analysis: compute p1 on row 1 */
/* test3.analysis: compute P2 on row 2 */
			if (j==0) { /* first one never changes */
			    m=ravptr[row][0];
			    if (m<-1) {	/* already computed -> copy it */
				ravals[nravals]=ravals[-m];
			    } else {	/* compute it */
				temp=-dt/(link->Cm*compt->Ra*coeffs[row*2]);
				ravals[nravals]=temp;
				diagterms[row]-=temp;
			    }
			} else {   /* has changed: resolve funcs index */
/* test2.analysis: use p4' on row 4 */
/* test3.analysis: use P8' on row 8 */
/* test3.analysis: use q13" on row 13 */
			    m=ravptr[row][0];
			    if ((m<=0)||(funcs[m]!=-1)) {
				printf("Error in %s: Bug #2 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    funcs[m]=nravals;	/* index is now resolved */
/* Search is necessary */
			    for (l=m; l<nfuncs; l++) {
				/* resolve copies of index also */
				if (funcs[l]==-m) {
				    funcs[l]=nravals;
				}
			    }
			}
			ravptr[row][0]=-nravals;  /* store for back elim */
			nravals++;	/* computed during simulation */
		    } else { /* asymmetric elements: RAXIAL connection */
/* test2.analysis: do row 4 */
			/* compute ravals for temp: left off-diag on row i
			**  RAXIAL connection */
/* test2.analysis: eliminate P4, contributed by row 3 */
			temp=-dt/(Cm*link->Ra);
			ravals[nravals++]=temp;
			diagterms[i]-=temp;
			/* compute ravals for diag[i]: right off-diag on row row
			**  AXIAL connection */
/* test2.analysis: compute P3, contributed by row 3 */
			temp=-dt/(link->Cm*link->Ra);
			ravals[nravals++]=temp;
			diagterms[row]-=temp;
		    }
		    if (symflag) {
			if (j==0) {
			    /* copy all the left-off diagonals which will
			    ** be changed first: if more than one kid */
			    for (l=1; l<nkid; l++) {
				funcs[nfuncs++]=COPY_ARRAY;
				ravptr[i][l+1]=nfuncs;
				funcs[nfuncs++]=-1;	/* mark as unresolved */
				n=kids[comptindex][l];
				link2=compts[n];
				row2=hnum[n];	/* convert to hines number */
/* test2.analysis: store p5, contributed by row 4 */
/* test3.analysis: store P14, contributed by row 8 */
/* test3.analysis: store q14, contributed by row 13 */
				/* parent: tail connection to kid */
				temp=-dt/(Cm*link2->Ra*coeffs[i*2+1]);
				ravals[nravals++]=temp;
				diagterms[i]-=temp;
			    }
			}
			/* compute all the changes to off-diagonals right of
			**  this one on the same row caused by this kid */
			for (l=j+1; l<nkid; l++) {
/* test2.analysis: compute p5', elimination of row 2 (S2) */
/* test3.analysis: compute P14', elimination of row 2 (S2) */
/* test3.analysis: compute q14', elimination of row 2 (s2) */
/* test3.analysis: compute q14", elimination of row 8 (S8') */
/* OPTIMIZATION: can also be a FASTSIB: see elimination of p13 and q14 */
			    funcs[nfuncs++]=SIBARRAY_ELIM;
			    m=ravptr[row][maxkids+l+1];
			    /* m < 0: from first sib -> won't change
			    ** m > 0: from later sib -> mark unresolved */
			    funcs[nfuncs++]=-m;	/* store index */
			    if (m==0) {
				printf("Error in %s: Bug #3 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				return(ERR);
			    }
			    m=ravptr[i][l+1];
			    if (m<=0) {
				printf("Error in %s: Bug #4 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				return(ERR);
			    }
			    funcs[nfuncs++]=-m;	/* mark as copy of unresolved */
			}
		    }
		}
	    }
	    n=0;	/* number of sib off-diagonal for this row */
	    if (symflag) {
	      if (parentno>-1) {
		nkid=nkids[parentno];
		if (!justcount) {
		    ravptr[i][maxkids+1]=0;	/* not used */
		    ravptr[i][maxkids+1+self]=0;	/* not used */
		    for (l=maxkids+nkid+1;l<=2*maxkids;l++)
						ravptr[i][l]=0; /* not used */
		}
		if (nkid<2) continue;		/* no sibs */
		/* Do siblings next */
		for (j=0; j<nkid; j++) {
		    k=kids[parentno][j];
		    link=compts[k];
		    row=hnum[k];	/* convert to hines number */
		    if ((nkid>2) && (self>0) && (j>0)) {
			/* compute all off diagonals except first one for this
			**  row as they will all change.
			**  kid: head cross connection to sib */
			if (justcount){
			     nfuncs+=2;
			     nravals++;
			} else {
			    temp=-dt/(Cm*link->Ra*coeffs[i*2]);
			    ravals[nravals++]=temp;
			    diagterms[i]-=temp;
			    /* copy this right-off diagonal which will change */
			    funcs[nfuncs++]=COPY_ARRAY;
/* test3.analysis: store S8 on row 8 for row 13 */
			    ravptr[i][maxkids+j+1]=nfuncs;
			    funcs[nfuncs++]=-1;	/* mark as unresolved */
			}
		    }
		    if (row>=i) continue;	/* no elimination here */
		    /* calculate scaling factor and eliminate left off-diag:
		    **   code to execute: temp = ravals[n++]/diag[row];
		    **               and: diag[i] -= ravals[n++]*temp;
		    **               and: results[i] -= results[row]*temp;
		    **   with ravals[n++] the left off-diagonal for row
		    */
		    if (justcount){
			nfuncs+=2;			/* FORWARD_ELIM */
			nravals+=2;
		    } else {
			funcs[nfuncs++]=FORWARD_ELIM;
			funcs[nfuncs++]=2*row;
/* test2.analysis: do row 4 */
/* test3.analysis: do row 13 */
			/* compute ravals for temp: left off-diag on row i
			**  kid: head cross connection to sib */
			if (n==0) { /* first one never changes */
/* test2.analysis: eliminate S4, contributed by row 2 */
/* test3.analysis: eliminate s13, contributed by row 2 */
			    temp=-dt/(Cm*link->Ra*coeffs[i*2]);
			    ravals[nravals++]=temp;
			    diagterms[i]-=temp;
			} else {   /* has changed: check if ptr correct! */
/* test3.analysis: eliminate S13, contributed by row 8 */
			    m=ravptr[i][maxkids+j+1];
			    if ((m<=0)||(funcs[m]!=-1)) {
				printf("Error in %s: Bug #5 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    funcs[m]=nravals;	/* index is now resolved */
			    found=0;
			    for (l=m; l<nfuncs; l++) {
				/* resolve copies of index also */
				if (funcs[l]==-m) {
				    funcs[l]=nravals;
				    found=1;
				}
			    }
			    if (found==0) {
				printf("Error in %s: Bug #-5 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    ravptr[i][maxkids+j+1]=nravals;  /* store for backward elim */
			    nravals++;	/* computed during simulation */
			}
			/* compute ravals diag[i]: right off-diag on row row
			**  kid: cross connection to sib */
/* test2.analysis: compute S2 on row 2 */
/* test3.analysis: compute S2 on row 2 for elimination S8 */
/* test3.analysis: compute s2 on row 2 for elimination s13 */
			if (n==0) { /* first one never changes */
			    temp=-dt/(link->Cm*compt->Ra*coeffs[row*2]);
			    ravptr[row][maxkids+self+1]=-nravals;
			    ravals[nravals++]=temp;
			    diagterms[row]-=temp;
			} else {   /* has changed: resolve funcs index */
/* test3.analysis: use s8' on row 8 for elimination S13 */
			    m=ravptr[row][maxkids+j+1];
			    if ((m<=0)||(funcs[m]!=-1)) {
				printf("Error in %s: Bug #6 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    funcs[m]=nravals;	/* index is now resolved */
			    found=0;
			    for (l=m; l<nfuncs; l++) {
				/* resolve copies of index also */
				if (funcs[l]==-m) {
				    funcs[l]=nravals;
				    found=1;
				}
			    }
			    if (found==0) {
				printf("Error in %s: Bug #-6 in hines_init %d %d: %d %d.\n",hsolve->name,i,j,m,nravals);
				return(ERR);
			    }
			    nravals++;	/* computed during simulation */
			    ravptr[row][maxkids+j+1]=0;
			}
		    }
		    if (self>0) {
			/* compute the changes to right parent off-diag */
/* test2.analysis: compute p4', elimination of row 2 (P2) */
/* test3.analysis: compute P8', elimination of row 2 (P2) */
/* test3.analysis: compute q13', elimination of row 2 (P2) */
/* test3.analysis: compute q13", elimination of row 8 (P8') */
			m=ravptr[row][0];
			if (m==-1) {	/* not used yet -> compute */
			    if (justcount) {
				nfuncs+=2;		/* FASTSIBARRAY_ELIM */
				nravals++;
			    } else {
				funcs[nfuncs++]=FASTSIBARRAY_ELIM;
				ravptr[row][0]=-nravals;
				temp=-dt/(link->Cm*parent->Ra*coeffs[row*2]);
				ravals[nravals++]=temp;
				diagterms[row]-=temp;
				m=ravptr[i][0];
				if (m<=0) {
				    printf("Error in %s: Bug #-7 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				    return(ERR);
				}
				funcs[nfuncs++]=-m; /* mark as copy unresolved*/
			    }
			} else {		/* use precomputed one */
			    if (justcount) {
				nfuncs+=3;		/* SIBARRAY_ELIM */
			    } else {
				funcs[nfuncs++]=SIBARRAY_ELIM;
				if ((m==-1)||(m==0)||((j>0)&&(m<0))) {
				    printf("Error in %s: Bug #7 in hines_init %d %d %d %d: %d.\n",hsolve->name,i,j,row,m,nravals);
				    return(ERR);
				}
				/* m < 0: from first sib -> won't change
				** m > 0: from later sib -> mark unresolved */
				funcs[nfuncs++]=-m;
				m=ravptr[i][0];
				if (m<=0) {
				    printf("Error in %s: Bug #-7 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				    return(ERR);
				}
				funcs[nfuncs++]=-m; /* mark as copy unresolved*/
			    }
			}

			/* compute the changes to other sib off-diagonals
			**  right of this one on the same row */
			for (l=j+1; l<nkid; l++) {
			    if (l==self) continue;
/* test3.analysis: compute S8', elimination of row 2 (s2) */
/* test3.analysis: compute S13', elimination of row 2 (S2) */
/* OPTIMIZATION: if constant copy it to ravals++, make new funcs code */
			    if (justcount) {
				nfuncs+=3;		/* SIBARRAY_ELIM */
			    } else {
				funcs[nfuncs++]=SIBARRAY_ELIM;
				m=ravptr[row][maxkids+l+1];
				if ((m==-1)||(m==0)||((j>0)&&(m<0))) {
				    printf("Error in %s: Bug #8 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				    return(ERR);
				}
				/* m < 0: from first sib -> won't change
				** m > 0: from later sib -> mark unresolved */
				funcs[nfuncs++]=-m;
				m=ravptr[i][maxkids+l+1];
				if (m<=0) {
				    printf("Error in %s: Bug #-8 in hines_init %d %d %d: %d %d.\n",hsolve->name,i,j,l,m,nravals);
				    return(ERR);
				}
				funcs[nfuncs++]=-m; /* mark as copy unresolved*/
			    }
			}
			n++;
		    }
		}
	      } else {
		for (l=maxkids+1;l<=2*maxkids;l++) ravptr[i][l]=0;/* not used */
	      }
	    }
	}
	}	/* closes the fwd_tree_start_pos/prev_was_root tracking block */
	/* Perform some controls */
	if (!justcount && symflag) {
	    /* Check if all ravptrs resolved */
	    for (l=0; l<nfuncs; l++) {
		if (funcs[l]<0) {
		    printf("Error in %s: Bug #9 in hines_init %d: %d.\n",hsolve->name,l,funcs[l]);
		    return(ERR);
		}
	    }
	    n=1;	/* ravptr[0][0]=-1 normally */
	    for (i=0;i<ncompts;i++) {
		for (l=n;l<=maxkids*2;l++) {
		    if ((((l==0)||(l>=maxkids))&&(ravptr[i][l]==-1))||
			(((l>0)&&(l<maxkids))&&(ravptr[i][l]))) {
			printf("Error in %s: Bug #10 in hines_init %d %d: %d.\n",hsolve->name,i,l,ravptr[i][l]);
			return(ERR);
		    }
		}
		n=0;
	    }
	}
        if (justcount){
            nfuncs++;
        } else {
            funcs[nfuncs++]=FINISH;	/* forward loop */
        }

	/* GENESIS 2.5 GPU-solve prep: capture the position where the backward
	** pass itself begins (right after the forward FINISH just emitted
	** above, before this loop's first iteration). This is the real
	** bwd_seg_start value for whichever tree turns out to be the
	** "soma done automatically" one at hnum==ncompts-1 -- it never enters
	** this loop (range stops at ncompts-2) so never gets a BWD_ROOT hit
	** below, and is fixed up from this captured position afterward. */
	int bwd_pass_start_pos = nfuncs;
	int bwd_pass_start_nravals = nravals;

	/* looping over all rows, doing backwards elimination */
	/* Eliminate contributions from upper rows: parents and sibs */
	for (i=ncompts-2;i>=0;i--) {	/* soma done automatically */
	    comptindex=elmnum[i];
	    compt=compts[comptindex];
	    Cm=compt->Cm;
	    parentno=parents[comptindex];
	if (!justcount && parentno == -1) {
		/* GENESIS 2.5 GPU-solve prep: record this tree's backward-pass
		** segment start, in the SAME tree slot the forward pass used
		** (looked up by root comptindex, since traversal order differs
		** between passes). bwd_raval_start captured here (CALC_RESULTS,
		** the only thing emitted for a root row, never touches nravals,
		** so this position is valid for whatever follows it too).
		** bwd_seg_start itself gets a "+1" fixup below (once we know
		** this root's own CALC_RESULTS is exactly 1 token) so it
		** points PAST that token -- see hines_struct.h kernel-entry
		** protocol comment for why a work-item must not re-process the
		** root's own CALC_RESULTS (it already solved that root itself,
		** uniformly, right after its forward segment). */
		int tidx = root_to_tree_idx[comptindex];
		if (tidx >= 0) {
		    hsolve->bwd_seg_start[tidx] = nfuncs;
		    hsolve->bwd_raval_start[tidx] = nravals;
		}
		if (getenv("GENESIS_DUMP_FUNCS")) {
		    fprintf(stderr, "FUNCS_DUMP: BWD_ROOT i=%d comptindex=%d nfuncs=%d nravals=%d tree=%d\n",
			    i, comptindex, nfuncs, nravals, tidx);
		}
	}
	    /* parentno==-1 means this row is itself the root of its own
	    ** disconnected subtree (e.g. one of several independent
	    ** single-compartment cells sharing one hsolve). Only the row
	    ** numbered ncompts-1 ("soma") is handled automatically by the
	    ** forward pass; any OTHER parentless row reaching this backward
	    ** loop has no parent/sib coupling to eliminate at all, so skip
	    ** straight to its own CALC_RESULTS (plain results[i]/diag[i]).
	    ** Without this guard, compts[-1]/hnum[-1] below read out of
	    ** bounds and corrupt/skip the update for that compartment. */
	    if (parentno != -1) {
	    if (symflag) {
		nkid=nkids[parentno];
		for (j=0; j<nkid; j++) {
		    if (kids[parentno][j]==comptindex) {
			self=j;
			break;
		    }
		}
	    } else {
		nkid=0;	/* no contribution from sibs */
	    }

	    /* eliminate parent contribution first */
	    link=compts[parentno];
	    row=hnum[parentno];	/* convert to hines number */
	    /* Backwards elimination of a coupled row
	    **   code to execute: results[i] -=  ravals[n++]*results[row];
	    **   with ravals[n++] the right off-diagonal of row i
	    */
/* test2.analysis: i is row 11 or 13 */
	    if (symflag && (self>0)) {
		/* right off-diagonal has changed */
		if (justcount) {
		    nfuncs+=3;
		} else {
/* POSSIBLE OPTIMIZATION: IN UNBRANCHED CABLE ROW = i + 1 */
/* test2.analysis: q13' */
		    funcs[nfuncs++]=SIBARRAY_ELIM;
		    if (ravptr[i][0]>=0) {
			printf("Error in %s: Bug #11 in hines_init %d %d: %d.\n",hsolve->name,i,0,ravptr[i][0]);
			return(ERR);
		    }
		    funcs[nfuncs++]=-ravptr[i][0];
		    funcs[nfuncs++]=2*row;
		}
	    } else {
		/* standard case: compute the right off-diagonal */
		if (justcount) {
		    nfuncs+=2;
		    nravals++;
		} else {
/* POSSIBLE OPTIMIZATION: IN UNBRANCHED CABLE ROW = i + 1 */
		    funcs[nfuncs++]=BACKWARD_ELIM;
		    funcs[nfuncs++]=2*row;
		    if (symflag) { /* symmetric elements */
			/* to parent or sibling: head connection */
/* test2.analysis: P11 (contributed by row 13) */
			ravals[nravals++]=-dt/(Cm*link->Ra*coeffs[i*2]);
		    } else { /* asymmetric element: AXIAL connection */
			ravals[nravals++]=-dt/(Cm*compt->Ra);
		    }
		}
	    }

	    /* symmetric compartments only: eliminate the sibs next */
	    for (j=0; j<nkid; j++) {
		k=kids[parentno][j];
		/* For symmetric comparts the right off-diagonal for parent may
		**   have been changed due to the elimination of a sibling left
		**   off-diagonal element: we compute this first
		*/
		link=compts[k];
		row=hnum[k];	/* convert to hines number */
		if (row<=i) continue;	/* connection to sib done in forward */
		/* Backwards elimination of a coupled row
		**   code to execute: results[i] -=  ravals[n++]*results[row];
		**   with ravals[n++] the right off-diagonal of row i
		*/
/* test2.analysis: i is row 11 */
		if (j>0) {
		    /* right off-diagonal has changed */
		    if (justcount) {
			nfuncs+=3;
		    } else {
/* POSSIBLE OPTIMIZATION: IN UNBRANCHED CABLE ROW = i + 1 */
/* test3.analysis: S8' */
			funcs[nfuncs++]=SIBARRAY_ELIM;
			if (ravptr[i][maxkids+j+1]>=0) {
			    printf("Error in %s: Bug #12 in hines_init %d %d %d: %d.\n",hsolve->name,i,j,maxkids+j+1,ravptr[i][maxkids+j+1]);
			    return(ERR);
			}
			funcs[nfuncs++]=-ravptr[i][maxkids+j+1];
			funcs[nfuncs++]=2*row;
		    }
		} else {
		    /* standard case: compute the right off-diagonal */
		    if (justcount) {
			nfuncs+=2;
			nravals++;
		    } else {
/* POSSIBLE OPTIMIZATION: IN UNBRANCHED CABLE ROW = i + 1 */
			funcs[nfuncs++]=BACKWARD_ELIM;
			funcs[nfuncs++]=2*row;
			/* to parent or sibling: head connection */
/* test2.analysis: s11 (contributed by row 12) */
			ravals[nravals++]=-dt/(Cm*link->Ra*coeffs[i*2]);
		    }
		}
	    }
	    } /* parentno != -1 */
	    /*
	    **  Compute final result:
	    **   code to execute: results[i] =  results[i+1]/diagonal[i+1];
	    **  For last row this can be done immediately, for others we
	    **   need to eliminate right off-diagonals first
	    */
            if (justcount){
		nfuncs++;
            } else {
                funcs[nfuncs++]=CALC_RESULTS;
            }
	}
	if (!justcount) {
	    /* GENESIS 2.5 GPU-solve prep: fix up bwd_seg_start/bwd_raval_start
	    ** now that the backward loop above has finished. Every tree that
	    ** got a real BWD_ROOT hit has bwd_seg_start pointing AT its own
	    ** root's CALC_RESULTS token (exactly 1 token, no operand) --
	    ** advance past it so a work-item can use the recorded value
	    ** directly, no skip needed at use time. The one tree that never
	    ** got a hit (hnum==ncompts-1, excluded from the loop's i>=0
	    ** range) gets the captured backward-pass-start position instead.
	    ** See hines_struct.h kernel-entry protocol comment. */
	    int tk, sentinel_count = 0;
	    for (tk = 0; tk < hsolve->n_trees; tk++) {
		if (hsolve->bwd_seg_start[tk] == -1) {
		    hsolve->bwd_seg_start[tk] = bwd_pass_start_pos;
		    hsolve->bwd_raval_start[tk] = bwd_pass_start_nravals;
		    sentinel_count++;
		} else {
		    hsolve->bwd_seg_start[tk] += 1;	/* skip root's own CALC_RESULTS */
		}
	    }
	    if (sentinel_count != 1) {
		printf("Error in %s: Bug #13 in hines_init: expected exactly 1 implicit-soma tree, found %d.\n",hsolve->name,sentinel_count);
		return(ERR);
	    }
	    if (getenv("GENESIS_DUMP_FUNCS")) {
		for (tk = 0; tk < hsolve->n_trees; tk++) {
		    fprintf(stderr, "FUNCS_DUMP: TREE tree=%d fwd_root_row=%d fwd_seg_start=%d fwd_raval_start=%d bwd_seg_start=%d bwd_raval_start=%d\n",
			    tk, hsolve->fwd_root_row[tk], hsolve->fwd_seg_start[tk],
			    hsolve->fwd_raval_start[tk], hsolve->bwd_seg_start[tk],
			    hsolve->bwd_raval_start[tk]);
		}
	    }
	}
        if (justcount){
            nfuncs++;
            hsolve->nfuncs=nfuncs;
            hsolve->nravals=nravals;
        } else {
            funcs[nfuncs++]=FINISH;
	    if (coeffs) free(coeffs);
	    if (diagterms) {
		/* copy to final storage */
		if (hsolve->chanmode>1) {
		    /* store in chip array */
		    for (i=0;i<ncompts;i++) {
			if (i==ncompts-1) {
			    j=hsolve->nchips-1;
			} else {
			    j=compchips[i+1]-1;
			}
			chip[j]=diagterms[i];
		    }
		} else {
		    /* store in diagonals array */
		    for (i=0;i<ncompts;i++) diagonals[i]=diagterms[i];
		}
		free(diagterms);
	    }
	}
	if (root_to_tree_idx) { free(root_to_tree_idx); root_to_tree_idx=NULL; }
	/* TEMPORARY DEBUG DUMP (Karol Chlasta, 2026-07-25) -- investigating
	** whether the combined funcs[] program for a multi-neuron hsolve is
	** block-diagonal (one FINISH pair per disconnected tree) or a single
	** flat program (one FINISH pair total). Gated on env var so it is
	** inert unless explicitly requested. Remove once GPU_HINES_SOLVE_DESIGN
	** is resolved and no longer needs this. */
	if (getenv("GENESIS_DUMP_FUNCS")) {
	    int di;
	    fprintf(stderr, "FUNCS_DUMP: justcount=%d ncompts=%d local_nfuncs=%d hsolve->nfuncs=%d hsolve->funcs=%p\n",
		    justcount, ncompts, nfuncs, hsolve->nfuncs, (void*)hsolve->funcs);
	    fprintf(stderr, "FUNCS_DUMP: parents[] = ");
	    for (di = 0; di < ncompts; di++) fprintf(stderr, "%d ", parents[di]);
	    fprintf(stderr, "\n");
	    fprintf(stderr, "FUNCS_DUMP: n_trees=%d\n", hsolve->n_trees);
	    fprintf(stderr, "FUNCS_DUMP: fwd_seg_start[] = ");
	    for (di = 0; di < hsolve->n_trees; di++) fprintf(stderr, "%d ", hsolve->fwd_seg_start[di]);
	    fprintf(stderr, "\n");
	    fprintf(stderr, "FUNCS_DUMP: bwd_seg_start[] = ");
	    for (di = 0; di < hsolve->n_trees; di++) fprintf(stderr, "%d ", hsolve->bwd_seg_start[di]);
	    fprintf(stderr, "\n");
	    fprintf(stderr, "FUNCS_DUMP: funcs[] = ");
	    if (hsolve->funcs == NULL) {
		fprintf(stderr, "(NULL -- not allocated at this call)");
	    } else {
	    for (di = 0; di < hsolve->nfuncs; di++) {
		int v = hsolve->funcs[di];
		if (v == FORWARD_ELIM) fprintf(stderr, "FE ");
		else if (v == SET_DIAG) fprintf(stderr, "SETD ");
		else if (v == SKIP_DIAG) fprintf(stderr, "SKIPD ");
		else if (v == FASTSIBARRAY_ELIM) fprintf(stderr, "FSIB ");
		else if (v == COPY_ARRAY) fprintf(stderr, "COPY ");
		else if (v == SIBARRAY_ELIM) fprintf(stderr, "SIB ");
		else if (v == FINISH) fprintf(stderr, "FINISH ");
		else fprintf(stderr, "%d ", v);
	    }
	    }
	    fprintf(stderr, "\n");
	}
        return(0);
}

/* copies diagonals from original chip array to chip array of the duplicate */
void copychipdiags(hsolve)
	Hsolve  *hsolve;
{
	int	i,nchip;
	int     ncompts=hsolve->ncompts;
	double	*chip=hsolve->chip;
	int	*compchips = hsolve->compchips;
	double	*origchip;

	origchip=hsolve->origsolve->chip;
	for (i=0;i<ncompts;i++) {
	    if (i==ncompts-1) {
		nchip=hsolve->nchips-1;
	    } else {
		nchip=compchips[i+1]-1;
	    }
	    chip[nchip]=origchip[nchip];
	}
}
