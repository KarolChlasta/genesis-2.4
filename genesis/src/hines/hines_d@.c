#include "hines_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_hsolve_type(){
struct hsolve_type var;Info info;char fields[2500];fields[0]='\0';info.name="hsolve_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="hsolve_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.path";info.offset=(caddr_t)(&(var.path))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"path");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field path\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.comptmode";info.offset=(caddr_t)(&(var.comptmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"comptmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field comptmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.chanmode";info.offset=(caddr_t)(&(var.chanmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"chanmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field chanmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.calcmode";info.offset=(caddr_t)(&(var.calcmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"calcmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field calcmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.no_elminfo";info.offset=(caddr_t)(&(var.no_elminfo))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"no_elminfo");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field no_elminfo\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.outclock";info.offset=(caddr_t)(&(var.outclock))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"outclock");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field outclock\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.storemode";info.offset=(caddr_t)(&(var.storemode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"storemode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field storemode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.computeIm";info.offset=(caddr_t)(&(var.computeIm))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"computeIm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field computeIm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.symflag";info.offset=(caddr_t)(&(var.symflag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"symflag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field symflag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ncompts";info.offset=(caddr_t)(&(var.ncompts))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ncompts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ncompts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compts";info.offset=(caddr_t)(&(var.compts))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(2);InfoHashPut(&info);strcat(fields,"compts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.parents";info.offset=(caddr_t)(&(var.parents))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"parents");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field parents\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nkids";info.offset=(caddr_t)(&(var.nkids))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"nkids");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nkids\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.kids";info.offset=(caddr_t)(&(var.kids))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(2);InfoHashPut(&info);strcat(fields,"kids");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field kids\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.hnum";info.offset=(caddr_t)(&(var.hnum))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"hnum");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field hnum\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.elmnum";info.offset=(caddr_t)(&(var.elmnum))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"elmnum");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field elmnum\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.results";info.offset=(caddr_t)(&(var.results))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"results");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field results\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.vm";info.offset=(caddr_t)(&(var.vm))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"vm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field vm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nfuncs";info.offset=(caddr_t)(&(var.nfuncs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nfuncs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nfuncs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.funcs";info.offset=(caddr_t)(&(var.funcs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"funcs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field funcs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ravptr";info.offset=(caddr_t)(&(var.ravptr))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(2);InfoHashPut(&info);strcat(fields,"ravptr");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ravptr\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.chan";info.offset=(caddr_t)(&(var.chan))-(caddr_t)(&var);		info.type="Cinfo";info.type_size=sizeof(Cinfo);__IFI(2);InfoHashPut(&info);strcat(fields,"chan");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field chan\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.msgcompts";info.offset=(caddr_t)(&(var.msgcompts))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"msgcompts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field msgcompts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.diagonals";info.offset=(caddr_t)(&(var.diagonals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"diagonals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field diagonals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.hh";info.offset=(caddr_t)(&(var.hh))-(caddr_t)(&var);		info.type="Tcinfo";info.type_size=sizeof(Tcinfo);__IFI(2);InfoHashPut(&info);strcat(fields,"hh");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field hh\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.piCompFlags";info.offset=(caddr_t)(&(var.piCompFlags))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"piCompFlags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field piCompFlags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nchildren";info.offset=(caddr_t)(&(var.nchildren))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nchildren");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nchildren\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.children";info.offset=(caddr_t)(&(var.children))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(2);InfoHashPut(&info);strcat(fields,"children");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field children\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childtypes";info.offset=(caddr_t)(&(var.childtypes))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"childtypes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childtypes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childdata";info.offset=(caddr_t)(&(var.childdata))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);__IFI(1);InfoHashPut(&info);strcat(fields,"childdata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childdata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childmsg";info.offset=(caddr_t)(&(var.childmsg))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childmsg");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childmsg\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childlink";info.offset=(caddr_t)(&(var.childlink))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childlink");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childlink\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childcode";info.offset=(caddr_t)(&(var.childcode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childcode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childcode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childpos";info.offset=(caddr_t)(&(var.childpos))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childpos");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childpos\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childstart";info.offset=(caddr_t)(&(var.childstart))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childstart");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childstart\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nravals";info.offset=(caddr_t)(&(var.nravals))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nravals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nravals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ravals";info.offset=(caddr_t)(&(var.ravals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"ravals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ravals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ininfo";info.offset=(caddr_t)(&(var.ininfo))-(caddr_t)(&var);		info.type="Iinfo";info.type_size=sizeof(Iinfo);__IFI(1);InfoHashPut(&info);strcat(fields,"ininfo");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ininfo\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.outinfo";info.offset=(caddr_t)(&(var.outinfo))-(caddr_t)(&var);		info.type="Oinfo";info.type_size=sizeof(Oinfo);__IFI(1);InfoHashPut(&info);strcat(fields,"outinfo");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field outinfo\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nchips";info.offset=(caddr_t)(&(var.nchips))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nchips");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nchips\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.chip";info.offset=(caddr_t)(&(var.chip))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"chip");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field chip\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nops";info.offset=(caddr_t)(&(var.nops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ops";info.offset=(caddr_t)(&(var.ops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"ops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.spikegen";info.offset=(caddr_t)(&(var.spikegen))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"spikegen");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field spikegen\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.vmlast";info.offset=(caddr_t)(&(var.vmlast))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"vmlast");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field vmlast\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nconcs";info.offset=(caddr_t)(&(var.nconcs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nconcs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nconcs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.conc";info.offset=(caddr_t)(&(var.conc))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"conc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field conc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.flux";info.offset=(caddr_t)(&(var.flux))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"flux");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field flux\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nconcchips";info.offset=(caddr_t)(&(var.nconcchips))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nconcchips");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nconcchips\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.concchip";info.offset=(caddr_t)(&(var.concchip))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"concchip");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field concchip\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nconcops";info.offset=(caddr_t)(&(var.nconcops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nconcops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nconcops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.concops";info.offset=(caddr_t)(&(var.concops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"concops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field concops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.fconc";info.offset=(caddr_t)(&(var.fconc))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"fconc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field fconc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ndiffs";info.offset=(caddr_t)(&(var.ndiffs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ndiffs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ndiffs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.fdiffs";info.offset=(caddr_t)(&(var.fdiffs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"fdiffs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field fdiffs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.dchild";info.offset=(caddr_t)(&(var.dchild))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"dchild");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field dchild\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.dconc";info.offset=(caddr_t)(&(var.dconc))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"dconc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field dconc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.maxshells";info.offset=(caddr_t)(&(var.maxshells))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"maxshells");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field maxshells\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.maxshcols";info.offset=(caddr_t)(&(var.maxshcols))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"maxshcols");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field maxshcols\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nshells";info.offset=(caddr_t)(&(var.nshells))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"nshells");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nshells\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nshrows";info.offset=(caddr_t)(&(var.nshrows))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"nshrows");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nshrows\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nshelms";info.offset=(caddr_t)(&(var.nshelms))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"nshelms");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nshelms\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nshfix";info.offset=(caddr_t)(&(var.nshfix))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"nshfix");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nshfix\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.covals0";info.offset=(caddr_t)(&(var.covals0))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"covals0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field covals0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.covals";info.offset=(caddr_t)(&(var.covals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"covals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field covals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.coresult";info.offset=(caddr_t)(&(var.coresult))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"coresult");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field coresult\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.codiag";info.offset=(caddr_t)(&(var.codiag))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"codiag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field codiag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.cores";info.offset=(caddr_t)(&(var.cores))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"cores");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field cores\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.fcoval";info.offset=(caddr_t)(&(var.fcoval))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"fcoval");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field fcoval\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.bufvals";info.offset=(caddr_t)(&(var.bufvals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"bufvals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field bufvals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.fbufval";info.offset=(caddr_t)(&(var.fbufval))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"fbufval");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field fbufval\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ngivals";info.offset=(caddr_t)(&(var.ngivals))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ngivals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ngivals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.givals";info.offset=(caddr_t)(&(var.givals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"givals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field givals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ovals";info.offset=(caddr_t)(&(var.ovals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"ovals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ovals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compgiv";info.offset=(caddr_t)(&(var.compgiv))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"compgiv");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compgiv\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childgiv";info.offset=(caddr_t)(&(var.childgiv))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childgiv");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childgiv\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childnames";info.offset=(caddr_t)(&(var.childnames))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childnames");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childnames\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nelm_names";info.offset=(caddr_t)(&(var.nelm_names))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nelm_names");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nelm_names\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.elm_names";info.offset=(caddr_t)(&(var.elm_names))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"elm_names");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field elm_names\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compchips";info.offset=(caddr_t)(&(var.compchips))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"compchips");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compchips\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compops";info.offset=(caddr_t)(&(var.compops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"compops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childops";info.offset=(caddr_t)(&(var.childops))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childops");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childops\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.childchips";info.offset=(caddr_t)(&(var.childchips))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"childchips");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field childchips\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.itotal";info.offset=(caddr_t)(&(var.itotal))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"itotal");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field itotal\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ntab";info.offset=(caddr_t)(&(var.ntab))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ntab");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ntab\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ncols";info.offset=(caddr_t)(&(var.ncols))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ncols");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ncols\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.tables";info.offset=(caddr_t)(&(var.tables))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"tables");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field tables\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.tabcols";info.offset=(caddr_t)(&(var.tabcols))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"tabcols");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field tabcols\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.tabinteg";info.offset=(caddr_t)(&(var.tabinteg))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"tabinteg");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field tabinteg\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.invdx";info.offset=(caddr_t)(&(var.invdx))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"invdx");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field invdx\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.xmin";info.offset=(caddr_t)(&(var.xmin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"xmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field xmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.xvals";info.offset=(caddr_t)(&(var.xvals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"xvals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field xvals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.xdivs";info.offset=(caddr_t)(&(var.xdivs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"xdivs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field xdivs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.tablist";info.offset=(caddr_t)(&(var.tablist))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"tablist");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field tablist\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.invdy";info.offset=(caddr_t)(&(var.invdy))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"invdy");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field invdy\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ymin";info.offset=(caddr_t)(&(var.ymin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"ymin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ymin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.yvals";info.offset=(caddr_t)(&(var.yvals))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"yvals");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field yvals\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ydivs";info.offset=(caddr_t)(&(var.ydivs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ydivs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ydivs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.sntab";info.offset=(caddr_t)(&(var.sntab))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"sntab");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field sntab\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.stablist";info.offset=(caddr_t)(&(var.stablist))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"stablist");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field stablist\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.dt";info.offset=(caddr_t)(&(var.dt))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"dt");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field dt\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.readflag";info.offset=(caddr_t)(&(var.readflag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"readflag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field readflag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.origsolve";info.offset=(caddr_t)(&(var.origsolve))-(caddr_t)(&var);		info.type="Hsolve";info.type_size=sizeof(Hsolve);__IFI(1);InfoHashPut(&info);strcat(fields,"origsolve");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field origsolve\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.comps";info.offset=(caddr_t)(&(var.comps))-(caddr_t)(&var);		info.type="Compinfo";info.type_size=sizeof(Compinfo);__IFI(1);InfoHashPut(&info);strcat(fields,"comps");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field comps\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.elmcomps";info.offset=(caddr_t)(&(var.elmcomps))-(caddr_t)(&var);		info.type="Compinfo";info.type_size=sizeof(Compinfo);__IFI(2);InfoHashPut(&info);strcat(fields,"elmcomps");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field elmcomps\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.numnodes";info.offset=(caddr_t)(&(var.numnodes))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"numnodes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field numnodes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.nodenumber";info.offset=(caddr_t)(&(var.nodenumber))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nodenumber");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field nodenumber\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.masternode";info.offset=(caddr_t)(&(var.masternode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"masternode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field masternode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.compnodes";info.offset=(caddr_t)(&(var.compnodes))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"compnodes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field compnodes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.startnodes";info.offset=(caddr_t)(&(var.startnodes))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"startnodes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field startnodes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.ncnode";info.offset=(caddr_t)(&(var.ncnode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"ncnode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field ncnode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.numsbytes";info.offset=(caddr_t)(&(var.numsbytes))-(caddr_t)(&var);		info.type="long";info.type_size=sizeof(long);__IFI(1);InfoHashPut(&info);strcat(fields,"numsbytes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field numsbytes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.numrbytes";info.offset=(caddr_t)(&(var.numrbytes))-(caddr_t)(&var);		info.type="long";info.type_size=sizeof(long);__IFI(1);InfoHashPut(&info);strcat(fields,"numrbytes");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field numrbytes\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.sendid";info.offset=(caddr_t)(&(var.sendid))-(caddr_t)(&var);		info.type="long";info.type_size=sizeof(long);__IFI(1);InfoHashPut(&info);strcat(fields,"sendid");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field sendid\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hsolve_type.netid";info.offset=(caddr_t)(&(var.netid))-(caddr_t)(&var);		info.type="long";info.type_size=sizeof(long);__IFI(1);InfoHashPut(&info);strcat(fields,"netid");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hsolve_type, field netid\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("hsolve_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_hines(){
INFO_hsolve_type();
}
