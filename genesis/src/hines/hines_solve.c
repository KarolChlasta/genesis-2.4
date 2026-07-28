static char rcsid[] = "$Id: hines_solve.c,v 1.2 2005/07/01 10:03:04 svitak Exp $";

/* Version EDS22d 98/09/30, Erik De Schutter, Caltech & BBF-UIA 4/92-9/98 */

/*
** $Log: hines_solve.c,v $
** Revision 1.2  2005/07/01 10:03:04  svitak
** Misc fixes to address compiler warnings, esp. providing explicit types
** for all functions and cleaning up unused variables.
**
** Revision 1.1.1.1  2005/06/14 04:38:32  svitak
** Import from snapshot of CalTech CVS tree of June 8, 2005
**
** Revision 1.4  1999/10/17 21:39:37  mhucka
** New version of Hines code from Erik De Schutter, dated 30 March 1999
** and including an update to hines.c from Erik from June 1999.  This version
** does not include changes to support Red Hat 6.0 and the Cray T3E, which
** will need to be incorporated in a separate revision update.
**
 * EDS22c revison: EDS BBF-UIA 98/09/29-98/09/30
 * Corrected bug in do_fast_hsolve
 *
 * EDS22c revison: EDS BBF-UIA 97/11/28-98/05/04
 * Rewrote funcs array and corresponding hsolve code
 * Made symmetric compartments work
 *
** Revision 1.1  1997/05/28 23:11:50  dhb
** Initial revision
**
*/

/* Contains the second loops for different chanmodes and solution methods:
**  a loop which executes the funcs array (do_crank_hsolve or
**     do_euler_hsolve): solve 13.18 of Mascagni. 
** in case of chanmode==2, a last loop updates Vm values (do_vm_update)
** For reasons of efficiency we have separate routines for symmetric
**  versus non symmetric cases
*/

#include "hines_ext.h"

/* trivial function that just loops over the funcs array and 
** performs the ops.  Does not update vm array.
*/
void do_fast_hsolve(hsolve)
    Hsolve  *hsolve;
{
    register int     *funcs=hsolve->funcs;
    register int     op;
    register double  temp = 0.0,resultval,diaval;
    register double  *results=hsolve->results;
    register double  *ravals=hsolve->ravals;
    register double  *raval=hsolve->ravals;
    register double  *resultvalue;

    op= *funcs++;
    if (hsolve->ncompts == 1) {	/* one compartment only! */
	*results = *results / *(results+1);
	return;
    } else {
	/* Do forwards elimination starting at row 1 (row 0 skipped) */
	resultvalue=results+2;
	resultval=*resultvalue;
	diaval=*(resultvalue+1);
    }

   while(1) {
        if (op == FORWARD_ELIM) {
            temp = *ravals++ / results[*funcs + 1];
	    diaval -= *ravals++ * temp;
	    resultval -= results[*funcs++] * temp;
        } else if (op == SET_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue++=diaval;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
        } else if (op == SKIP_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue=diaval;
	    resultvalue+=3;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
	} else if (op == FASTSIBARRAY_ELIM) {
	    raval[*funcs++] -= *ravals++ * temp;
	} else if (op==COPY_ARRAY) {
	    raval[*funcs++] = *ravals++;
	} else if (op == SIBARRAY_ELIM) {
	    raval[*(funcs+1)] -= raval[*funcs] * temp;
	    funcs+=2;
        } else { /* FINISH */
            break;
        }
        op= *funcs++;
    }
    /* store result last row */
    *resultvalue=resultval/diaval;
    resultvalue-=2;
    resultval=*resultvalue;

    /* Do backwards elimination */
    while(1) {
        op= *funcs++;
        if (op == BACKWARD_ELIM) {
	    resultval -= *ravals++ * results[*funcs++];
        } else if (op == CALC_RESULTS) {
            *resultvalue = resultval / *(resultvalue+1);
            resultvalue-=2;
	    resultval=*resultvalue;
	} else if (op == SIBARRAY_ELIM) {
	    resultval -= raval[*funcs] * results[*(funcs+1)];
	    funcs+=2;
        } else { /* FINISH */
            break;
	}
    }
}

/* Simple function for putting data values back into elements,
** when the chip array is being used */
void do_vm_update(hsolve)
	Hsolve	*hsolve;
{
	register struct compartment_type **compts;
	register int	*elmnum;
	register double	*vm;

	compts = (struct compartment_type **)(hsolve->compts);
	elmnum = hsolve->elmnum;
	vm = hsolve->vm;

	/* update all comp values */
	for(vm=hsolve->vm;vm<&(hsolve->vm[hsolve->ncompts]);vm++) {
		compts[*elmnum++]->Vm = *vm;
	}
}

/* trivial function that just loops over the funcs array and
** performs the ops for symmetric compartments. */
/* performs also final Crank-Nicolson interpolation */
void do_crank_hsolve(hsolve)
    Hsolve  *hsolve;
{
    register int     *funcs=hsolve->funcs;
    register int     op;
    register double  temp = 0.0,resultval,diaval;
    register double  *results=hsolve->results;
    register double  *ravals=hsolve->ravals;
    register double  *raval=hsolve->ravals;
    register double  *vm=hsolve->vmlast;
    register double  *resultvalue;

    op= *funcs++;
    if (hsolve->ncompts == 1) {	/* one compartment only! */
	resultval = *results / *(results+1);
	*vm = resultval + resultval - *vm;
	return;
    } else {
	/* Do forwards elimination starting at row 1 (row 0 skipped) */
	resultvalue=results+2;
	resultval=*resultvalue;
	diaval=*(resultvalue+1);
    }

   while(1) {
        if (op == FORWARD_ELIM) {
            temp = *ravals++ / results[*funcs + 1];
	    diaval -= *ravals++ * temp;
	    resultval -= results[*funcs++] * temp;
        } else if (op == SET_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue++=diaval;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
        } else if (op == SKIP_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue=diaval;
	    resultvalue+=3;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
	} else if (op == FASTSIBARRAY_ELIM) {
	    raval[*funcs++] -= *ravals++ * temp;
	} else if (op==COPY_ARRAY) {
	    raval[*funcs++] = *ravals++;
	} else if (op == SIBARRAY_ELIM) {
	    raval[*(funcs+1)] -= raval[*funcs] * temp;
	    funcs+=2;
        } else { /* FINISH */
            break;
        }
        op= *funcs++;
    }
    /* store result last row */
    resultval=resultval/diaval;
    *vm = resultval + resultval - *vm;
    *resultvalue=resultval;
    resultvalue-=2;
    resultval=*resultvalue;

    /* Do backwards elimination */
    while(1) {
        op= *funcs++;
        if (op == BACKWARD_ELIM) {
	    resultval -= *ravals++ * results[*funcs++];
        } else if (op == CALC_RESULTS) {
            resultval = resultval / *(resultvalue+1);
	    vm--;
	    *vm = resultval + resultval - *vm;
	    *resultvalue=resultval;
            resultvalue-=2;
	    resultval=*resultvalue;
	} else if (op == SIBARRAY_ELIM) {
	    resultval -= raval[*funcs] * results[*(funcs+1)];
	    funcs+=2;
        } else { /* FINISH */
            break;
	}
    }
}

/* trivial function that just loops over the funcs array and
** performs the ops for symmetric compartments. */
/* performs also final Euler storage */
void do_euler_hsolve(hsolve)
    Hsolve  *hsolve;
{
    register int     *funcs=hsolve->funcs;
    register int     op;
    register double  temp = 0.0,resultval,diaval;
    register double  *results=hsolve->results;
    register double  *ravals=hsolve->ravals;
    register double  *raval=hsolve->ravals;
    register double  *vm=hsolve->vmlast;
    register double  *resultvalue;

    op= *funcs++;
    if (hsolve->ncompts == 1) {	/* one compartment only! */
	*vm = *results / *(results+1);
	return;
    } else {
	/* Do forwards elimination starting at row 1 (row 0 skipped) */
	resultvalue=results+2;
	resultval=*resultvalue;
	diaval=*(resultvalue+1);
    }

   while(1) {
        if (op == FORWARD_ELIM) {
            temp = *ravals++ / results[*funcs + 1];
	    diaval -= *ravals++ * temp;
	    resultval -= results[*funcs++] * temp;
        } else if (op == SET_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue++=diaval;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
        } else if (op == SKIP_DIAG) {
	    *resultvalue++=resultval;
	    *resultvalue=diaval;
	    resultvalue+=3;
	    resultval=*resultvalue;
	    diaval=*(resultvalue+1);
	} else if (op == FASTSIBARRAY_ELIM) {
	    raval[*funcs++] -= *ravals++ * temp;
	} else if (op==COPY_ARRAY) {
	    raval[*funcs++] = *ravals++;
	} else if (op == SIBARRAY_ELIM) {
	    raval[*(funcs+1)] -= raval[*funcs] * temp;
	    funcs+=2;
        } else { /* FINISH */
            break;
        }
        op= *funcs++;
    }
    /* store result last row */
    *vm=*resultvalue=resultval/diaval;
    resultvalue-=2;
    resultval=*resultvalue;

    /* Do backwards elimination */
    while(1) {
        op= *funcs++;
        if (op == BACKWARD_ELIM) {
	    resultval -= *ravals++ * results[*funcs++];
        } else if (op == CALC_RESULTS) {
	    vm--;
            *vm=*resultvalue = resultval / *(resultvalue+1);
            resultvalue-=2;
	    resultval=*resultvalue;
	} else if (op == SIBARRAY_ELIM) {
	    resultval -= raval[*funcs] * results[*(funcs+1)];
	    funcs+=2;
        } else { /* FINISH */
            break;
	}
    }
}

/* GENESIS 2.5 GPU-solve prep (Karol Chlasta, 2026-07-25): must be called
** BEFORE do_euler_hsolve/do_crank_hsolve -- it snapshots results[]/
** ravals[] as populated by that step's channel-kinetics update, before
** the real solve mutates them in place (SET_DIAG/SKIP_DIAG fold
** children in, CALC_RESULTS divides -- both write back into results[]).
** do_pertree_validate operates on this snapshot, not the live (already
** solved, no longer representing per-compartment BASE values) arrays --
** running it on the live post-solve state would fold already-folded
** contributions a second time, producing wrong numbers (found
** empirically 2026-07-25: this was the actual remaining source of
** mismatches after the tree-boundary and bootstrap fixes below). */
static double *pertree_results_snap = NULL;
static double *pertree_ravals_snap = NULL;
static int    pertree_snap_ncompts = 0;
static int    pertree_snap_nravals = 0;

void do_pertree_snapshot(hsolve)
    Hsolve  *hsolve;
{
    if (pertree_snap_ncompts != hsolve->ncompts) {
	if (pertree_results_snap) free(pertree_results_snap);
	pertree_results_snap = (double *)malloc(2*hsolve->ncompts*sizeof(double));
	pertree_snap_ncompts = hsolve->ncompts;
    }
    if (pertree_snap_nravals != hsolve->nravals) {
	if (pertree_ravals_snap) free(pertree_ravals_snap);
	pertree_ravals_snap = (double *)malloc(hsolve->nravals*sizeof(double));
	pertree_snap_nravals = hsolve->nravals;
    }
    memcpy(pertree_results_snap, hsolve->results, 2*hsolve->ncompts*sizeof(double));
    memcpy(pertree_ravals_snap, hsolve->ravals, hsolve->nravals*sizeof(double));
}

/* GENESIS 2.5 GPU-solve prep (Karol Chlasta, 2026-07-25): CPU-side
** reference implementation of the per-tree GPU kernel-entry protocol
** documented in hines_struct.h (fwd_seg_start/bwd_seg_start/
** fwd_root_row/fwd_raval_start/bwd_raval_start). Runs each tree's
** forward+root-solve+backward sequence in isolation, exactly as a
** future GPU work-item would (on the do_pertree_snapshot'd pre-solve
** state), and compares the result against hsolve->vm[] as already
** written by a preceding real do_euler_hsolve/do_crank_hsolve call for
** the same step. Exists to validate the protocol in plain, easy-to-
** debug C before writing OpenCL/CUDA against it. Gated on
** GENESIS_VALIDATE_PERTREE=1 by the caller in hines.c; zero cost/
** behavior change when not called. Must run do_pertree_snapshot first
** (same step, before the real solve) -- never touches hsolve->results/
** ravals or hsolve->vm[], all reads/writes are on the private snapshot. */
void do_pertree_validate(hsolve)
    Hsolve  *hsolve;
{
    double  *results = pertree_results_snap;
    double  *ravals0 = pertree_ravals_snap;
    double  *raval = pertree_ravals_snap;	/* absolute indexing, shared snapshot buffer */
    int     *funcs0 = hsolve->funcs;
    int     k, mismatches = 0;
    double  tol = 1e-9;

    for (k = 0; k < hsolve->n_trees; k++) {
	int     *funcs = funcs0 + hsolve->fwd_seg_start[k];
	double  *ravals = ravals0 + hsolve->fwd_raval_start[k];
	int     root_row = hsolve->fwd_root_row[k];
	int     first_row = (k == 0) ? 0 : hsolve->fwd_root_row[k-1] + 1;
	int     seed_row;
	double  *resultvalue;
	double  resultval, diaval, my_vm, ref_vm, temp = 0.0;
	int     op, fwd_seg_end, seg_end, kk;

	/* This tree's forward range ends where the next tree's begins, or
	** (last tree) at the forward-pass FINISH position -- derived as
	** bwd_seg_start[n_trees-1]-1, since the sentinel tree (always last
	** by discovery/index order -- its root is the global last row) has
	** its bwd_seg_start recorded as exactly the backward-pass-start
	** position, i.e. one past forward FINISH (see hines_init.c's
	** post-backward-loop fixup). */
	fwd_seg_end = (k+1 < hsolve->n_trees)
	    ? hsolve->fwd_seg_start[k+1]
	    : hsolve->bwd_seg_start[hsolve->n_trees-1] - 1;

	/* Bootstrap: skip this tree's leading transition opcode instead of
	** executing it via the generic interpreter (see GPU_HINES_SOLVE_
	** DESIGN.md "kernel design groundwork" -- traced concretely on
	** funcs_dump_test.g 2026-07-25). Executing it for real would flush
	** (write) into results[] at a position belonging to the PREVIOUS
	** tree -- the single-threaded code relies on that write to persist
	** the previous tree's root value, but a standalone work-item
	** already provides that value itself via the root-solve write-back
	** below, making the flush redundant AND, for a true parallel
	** kernel, a cross-tree data race. Only the resulting LOAD position
	** matters, so it is replicated directly:
	**   - leading SET_DIAG (first_row IS the root, a 1-compt tree, or
	**     -- not yet handled -- first_row has siblings/hassiblefts):
	**     loads first_row's own base value directly.
	**   - leading SKIP_DIAG (the common case: first_row is a plain
	**     unbranched leaf): the single-threaded flush+advance lands 2
	**     rows further than a SET_DIAG would, i.e. loads first_row+1's
	**     own base value instead -- first_row's own value is folded in
	**     normally moments later, via the next row's FORWARD_ELIM
	**     referencing it by absolute index (channel-update already
	**     populated it; no dependency on this tree's own bootstrap).
	**   - leading FORWARD_ELIM directly (no transition opcode at all):
	**     only possible for k==0 -- the global i<=1 bootstrap exclusion
	**     in do_euler_hsolve (resultvalue=results+2, "row 0 skipped")
	**     means row 0 (and row 1, whose own decision is also excluded)
	**     never get an explicit SET_DIAG/SKIP_DIAG; replicate that
	**     exact bootstrap by seeding from row 1 directly. */
	op = *funcs;
	if (op == SET_DIAG) {
	    seed_row = first_row;
	    funcs++;
	} else if (op == SKIP_DIAG) {
	    seed_row = first_row + 1;
	    funcs++;
	} else if (k == 0 && op == FORWARD_ELIM) {
	    seed_row = 1;
	} else {
	    fprintf(stderr, "PERTREE_MISMATCH: tree=%d unhandled leading opcode %d (branching bootstrap not yet implemented)\n", k, op);
	    mismatches++;
	    continue;
	}
	resultvalue = &results[2*seed_row];
	resultval = *resultvalue;
	diaval = *(resultvalue+1);

	/* forward pass: process every opcode belonging to this tree, up to
	** (not including) fwd_seg_end. SET_DIAG/SKIP_DIAG occur once per
	** "un-fused" row transition WITHIN a tree (not just at its very
	** start) -- e.g. an 8-compartment linear chain emits one for
	** nearly every row -- and must be executed normally here: their
	** flush target (resultvalue) is by construction always a slot
	** belonging to THIS tree's own row range (safe, no cross-tree
	** write), unlike the leading transition token skipped above. */
	while ((funcs - funcs0) < fwd_seg_end) {
	    op = *funcs++;
	    if (op == FORWARD_ELIM) {
		temp = *ravals++ / results[*funcs + 1];
		diaval -= *ravals++ * temp;
		resultval -= results[*funcs++] * temp;
	    } else if (op == SET_DIAG) {
		*resultvalue++ = resultval;
		*resultvalue++ = diaval;
		resultval = *resultvalue;
		diaval = *(resultvalue + 1);
	    } else if (op == SKIP_DIAG) {
		*resultvalue++ = resultval;
		*resultvalue = diaval;
		resultvalue += 3;
		resultval = *resultvalue;
		diaval = *(resultvalue + 1);
	    } else if (op == FASTSIBARRAY_ELIM) {
		raval[*funcs++] -= *ravals++ * temp;
	    } else if (op == COPY_ARRAY) {
		raval[*funcs++] = *ravals++;
	    } else if (op == SIBARRAY_ELIM) {
		raval[*(funcs+1)] -= raval[*funcs] * temp;
		funcs += 2;
	    } else {
		fprintf(stderr, "PERTREE_MISMATCH: tree=%d unexpected opcode %d in forward segment\n", k, op);
		mismatches++;
		break;
	    }
	}

	/* root solve: uniform for every tree regardless of whether the
	** single-threaded code happened to handle it via the forward
	** pass's "last row" special case or the backward pass's
	** CALC_RESULTS for this particular combined-program layout. */
	resultval = resultval / diaval;
	results[2*root_row] = resultval;	/* backward pass reads the parent's
						** solved value via this absolute
						** index -- must persist it, exactly
						** as do_euler_hsolve's own
						** "*resultvalue=resultval/diaval"
						** does for the single-threaded case */
	my_vm = resultval;
	ref_vm = hsolve->vm[root_row];
	if (fabs(my_vm - ref_vm) > tol) {
	    fprintf(stderr, "PERTREE_MISMATCH: tree=%d row=%d(root) mine=%.12g ref=%.12g diff=%.3g\n",
		    k, root_row, my_vm, ref_vm, my_vm - ref_vm);
	    mismatches++;
	}

	/* backward pass: this tree's own rows strictly below its root, if
	** any. Range end = whichever OTHER (non-sentinel) tree's
	** bwd_seg_start[] is numerically next after ours, MINUS 1, or
	** hsolve->nfuncs-1 (excluding the trailing global FINISH) if none.
	** The "-1" matters: bwd_seg_start[kk] for a non-sentinel tree
	** already points PAST that tree's own root's CALC_RESULTS token
	** (hines_init.c's post-backward-loop fixup adds 1 so kk's own
	** entry point needs no further adjustment) -- but used as tree k's
	** upper bound, that extra token (kk's root's CALC_RESULTS) sits
	** BETWEEN tree k's real end and kk's real start, and belongs to kk,
	** not k. Found empirically 2026-07-25: without the "-1" here, the
	** tree with the globally-smallest bwd_seg_start (the sentinel,
	** whose value is NOT root+1 but the true backward-pass start) was
	** fine, but every OTHER tree's segment silently ran one token past
	** its true end into whichever tree's root happened to come next. */
	seg_end = hsolve->nfuncs - 1;	/* exclude the trailing global FINISH token */
	for (kk = 0; kk < hsolve->n_trees; kk++) {
	    if (hsolve->bwd_seg_start[kk] > hsolve->bwd_seg_start[k]
		&& hsolve->bwd_seg_start[kk] - 1 < seg_end) {
		seg_end = hsolve->bwd_seg_start[kk] - 1;
	    }
	}
	if (seg_end > hsolve->bwd_seg_start[k]) {
	    int     *bfuncs = funcs0 + hsolve->bwd_seg_start[k];
	    double  *bravals = ravals0 + hsolve->bwd_raval_start[k];
	    /* first row below the root: its own carried-over (not yet
	    ** divided) forward value, exactly what the single-threaded
	    ** loop's own resultvalue-=2/resultval=*resultvalue step would
	    ** have produced right after finishing this root's CALC_RESULTS. */
	    double  *bresultvalue = &results[2*(root_row - 1)];
	    double  bresultval = *bresultvalue;
	    int     brow;

	    while ((bfuncs - funcs0) < seg_end) {
		op = *bfuncs++;
		if (op == BACKWARD_ELIM) {
		    bresultval -= *bravals++ * results[*bfuncs++];
		} else if (op == CALC_RESULTS) {
		    brow = (bresultvalue - results) / 2;
		    bresultval = bresultval / *(bresultvalue + 1);
		    *bresultvalue = bresultval;	/* persist -- a lower row's own
						** BACKWARD_ELIM may reference this
						** row's solved value via absolute
						** index, same as do_euler_hsolve's
						** own "*resultvalue=..." write */
		    my_vm = bresultval;
		    ref_vm = hsolve->vm[brow];
		    if (fabs(my_vm - ref_vm) > tol) {
			fprintf(stderr, "PERTREE_MISMATCH: tree=%d row=%d mine=%.12g ref=%.12g diff=%.3g\n",
				k, brow, my_vm, ref_vm, my_vm - ref_vm);
			mismatches++;
		    }
		    bresultvalue -= 2;
		    bresultval = *bresultvalue;
		} else if (op == SIBARRAY_ELIM) {
		    bresultval -= raval[*bfuncs] * results[*(bfuncs+1)];
		    bfuncs += 2;
		} else {
		    fprintf(stderr, "PERTREE_MISMATCH: tree=%d unexpected opcode %d in backward segment\n", k, op);
		    mismatches++;
		    break;
		}
	    }
	}
    }
    if (getenv("GENESIS_VALIDATE_PERTREE")) {
	fprintf(stderr, "PERTREE_VALIDATE: n_trees=%d mismatches=%d\n", hsolve->n_trees, mismatches);
    }
}
