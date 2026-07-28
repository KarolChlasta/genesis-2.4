#include "kin_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_pool_type(){
struct pool_type var;Info info;char fields[2500];fields[0]='\0';info.name="pool_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="pool_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.CoTotal";info.offset=(caddr_t)(&(var.CoTotal))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoTotal");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field CoTotal\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.CoInit";info.offset=(caddr_t)(&(var.CoInit))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoInit");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field CoInit\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.Co";info.offset=(caddr_t)(&(var.Co))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Co");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field Co\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.CoRemaining";info.offset=(caddr_t)(&(var.CoRemaining))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoRemaining");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field CoRemaining\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.CoMin";info.offset=(caddr_t)(&(var.CoMin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoMin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field CoMin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.n";info.offset=(caddr_t)(&(var.n))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"n");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field n\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nInit";info.offset=(caddr_t)(&(var.nInit))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nInit");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nInit\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nTotal";info.offset=(caddr_t)(&(var.nTotal))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nTotal");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nTotal\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nRemaining";info.offset=(caddr_t)(&(var.nRemaining))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nRemaining");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nRemaining\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.nMin";info.offset=(caddr_t)(&(var.nMin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nMin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field nMin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.vol";info.offset=(caddr_t)(&(var.vol))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"vol");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field vol\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.slave_enable";info.offset=(caddr_t)(&(var.slave_enable))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"slave_enable");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field slave_enable\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.keepconc";info.offset=(caddr_t)(&(var.keepconc))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"keepconc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field keepconc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.consv_flag";info.offset=(caddr_t)(&(var.consv_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"consv_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field consv_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.stoch_flag";info.offset=(caddr_t)(&(var.stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.mirror_src";info.offset=(caddr_t)(&(var.mirror_src))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"mirror_src");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field mirror_src\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgdata";info.offset=(caddr_t)(&(var.msgdata))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"msgdata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgdata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.mirrormsgoffset";info.offset=(caddr_t)(&(var.mirrormsgoffset))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"mirrormsgoffset");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field mirrormsgoffset\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.msgcount";info.offset=(caddr_t)((var.msgcount))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IND(1);__IDS(0,8);InfoHashPut(&info);strcat(fields,"msgcount");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field msgcount\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.was_slaved";info.offset=(caddr_t)(&(var.was_slaved))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"was_slaved");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field was_slaved\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_type.oldmsgmode";info.offset=(caddr_t)(&(var.oldmsgmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"oldmsgmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_type, field oldmsgmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("pool_type",fields);
}
void INFO_reac_type(){
struct reac_type var;Info info;char fields[2500];fields[0]='\0';info.name="reac_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="reac_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.A";info.offset=(caddr_t)(&(var.A))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.B";info.offset=(caddr_t)(&(var.B))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.kf";info.offset=(caddr_t)(&(var.kf))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"kf");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field kf\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.kb";info.offset=(caddr_t)(&(var.kb))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"kb");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field kb\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.stoch_flag";info.offset=(caddr_t)(&(var.stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.sub_stoch_flag";info.offset=(caddr_t)(&(var.sub_stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"sub_stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field sub_stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.prd_stoch_flag";info.offset=(caddr_t)(&(var.prd_stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"prd_stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field prd_stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.dep_graph_index";info.offset=(caddr_t)(&(var.dep_graph_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"dep_graph_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field dep_graph_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgdata";info.offset=(caddr_t)(&(var.msgdata))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"msgdata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgdata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.se";info.offset=(caddr_t)((var.se))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);__IND(1);__IDS(0,50);InfoHashPut(&info);strcat(fields,"se");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field se\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.msgcount";info.offset=(caddr_t)((var.msgcount))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IND(1);__IDS(0,2);InfoHashPut(&info);strcat(fields,"msgcount");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field msgcount\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_type.oldmsgmode";info.offset=(caddr_t)(&(var.oldmsgmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"oldmsgmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_type, field oldmsgmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("reac_type",fields);
}
void INFO_enz_type(){
struct enz_type var;Info info;char fields[2500];fields[0]='\0';info.name="enz_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="enz_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.CoComplexInit";info.offset=(caddr_t)(&(var.CoComplexInit))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoComplexInit");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field CoComplexInit\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.CoComplex";info.offset=(caddr_t)(&(var.CoComplex))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"CoComplex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field CoComplex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.nComplexInit";info.offset=(caddr_t)(&(var.nComplexInit))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nComplexInit");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field nComplexInit\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.nComplex";info.offset=(caddr_t)(&(var.nComplex))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nComplex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field nComplex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.vol";info.offset=(caddr_t)(&(var.vol))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"vol");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field vol\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.sA";info.offset=(caddr_t)(&(var.sA))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"sA");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field sA\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.pA";info.offset=(caddr_t)(&(var.pA))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"pA");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field pA\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.eA";info.offset=(caddr_t)(&(var.eA))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"eA");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field eA\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.B";info.offset=(caddr_t)(&(var.B))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.k1";info.offset=(caddr_t)(&(var.k1))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"k1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field k1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.k2";info.offset=(caddr_t)(&(var.k2))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"k2");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field k2\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.k3";info.offset=(caddr_t)(&(var.k3))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"k3");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field k3\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.keepconc";info.offset=(caddr_t)(&(var.keepconc))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"keepconc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field keepconc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.usecomplex";info.offset=(caddr_t)(&(var.usecomplex))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"usecomplex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field usecomplex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.stoch_flag";info.offset=(caddr_t)(&(var.stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.sub_stoch_flag";info.offset=(caddr_t)(&(var.sub_stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"sub_stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field sub_stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.complex_stoch_flag";info.offset=(caddr_t)(&(var.complex_stoch_flag))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"complex_stoch_flag");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field complex_stoch_flag\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.propensity_problem";info.offset=(caddr_t)(&(var.propensity_problem))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"propensity_problem");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field propensity_problem\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.dep_graph_index";info.offset=(caddr_t)(&(var.dep_graph_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"dep_graph_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field dep_graph_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.ksum";info.offset=(caddr_t)(&(var.ksum))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"ksum");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field ksum\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgdata";info.offset=(caddr_t)(&(var.msgdata))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"msgdata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgdata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.se";info.offset=(caddr_t)((var.se))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);__IND(1);__IDS(0,50);InfoHashPut(&info);strcat(fields,"se");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field se\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.msgcount";info.offset=(caddr_t)((var.msgcount))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IND(1);__IDS(0,5);InfoHashPut(&info);strcat(fields,"msgcount");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field msgcount\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_type.oldmsgmode";info.offset=(caddr_t)(&(var.oldmsgmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"oldmsgmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_type, field oldmsgmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("enz_type",fields);
}
void INFO_concchan_type(){
struct concchan_type var;Info info;char fields[2500];fields[0]='\0';info.name="concchan_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="concchan_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.A";info.offset=(caddr_t)(&(var.A))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.B";info.offset=(caddr_t)(&(var.B))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.perm";info.offset=(caddr_t)(&(var.perm))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"perm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field perm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.gmax";info.offset=(caddr_t)(&(var.gmax))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"gmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field gmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.n";info.offset=(caddr_t)(&(var.n))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"n");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field n\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.Vm";info.offset=(caddr_t)(&(var.Vm))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Vm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field Vm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.is_active";info.offset=(caddr_t)(&(var.is_active))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"is_active");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field is_active\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_type.use_nernst";info.offset=(caddr_t)(&(var.use_nernst))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"use_nernst");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_type, field use_nernst\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("concchan_type",fields);
}
void INFO_pool_coeff_type(){
struct pool_coeff_type var;Info info;char fields[2500];fields[0]='\0';info.name="pool_coeff_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="pool_coeff_type.pool";info.offset=(caddr_t)(&(var.pool))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"pool");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_coeff_type, field pool\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="pool_coeff_type.init";info.offset=(caddr_t)(&(var.init))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"init");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object pool_coeff_type, field init\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("pool_coeff_type",fields);
}
void INFO_reac_coeff_type(){
struct reac_coeff_type var;Info info;char fields[2500];fields[0]='\0';info.name="reac_coeff_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="reac_coeff_type.pools";info.offset=(caddr_t)(&(var.pools))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"pools");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_coeff_type, field pools\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_coeff_type.kf";info.offset=(caddr_t)(&(var.kf))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"kf");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_coeff_type, field kf\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="reac_coeff_type.kb";info.offset=(caddr_t)(&(var.kb))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"kb");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object reac_coeff_type, field kb\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("reac_coeff_type",fields);
}
void INFO_enz_coeff_type(){
struct enz_coeff_type var;Info info;char fields[2500];fields[0]='\0';info.name="enz_coeff_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="enz_coeff_type.k1";info.offset=(caddr_t)(&(var.k1))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"k1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field k1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.k2";info.offset=(caddr_t)(&(var.k2))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"k2");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field k2\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.k3";info.offset=(caddr_t)(&(var.k3))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"k3");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field k3\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.enzcomplexinit";info.offset=(caddr_t)(&(var.enzcomplexinit))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"enzcomplexinit");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field enzcomplexinit\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.enzcomplex";info.offset=(caddr_t)(&(var.enzcomplex))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"enzcomplex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field enzcomplex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.enz";info.offset=(caddr_t)(&(var.enz))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"enz");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field enz\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.prd";info.offset=(caddr_t)(&(var.prd))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"prd");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field prd\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="enz_coeff_type.sub";info.offset=(caddr_t)(&(var.sub))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"sub");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object enz_coeff_type, field sub\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("enz_coeff_type",fields);
}
void INFO_concchan_coeff_type(){
struct concchan_coeff_type var;Info info;char fields[2500];fields[0]='\0';info.name="concchan_coeff_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="concchan_coeff_type.chan";info.offset=(caddr_t)(&(var.chan))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"chan");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_coeff_type, field chan\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_coeff_type.perm_by_vol1";info.offset=(caddr_t)(&(var.perm_by_vol1))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"perm_by_vol1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_coeff_type, field perm_by_vol1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_coeff_type.src";info.offset=(caddr_t)(&(var.src))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"src");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_coeff_type, field src\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_coeff_type.perm_by_vol2";info.offset=(caddr_t)(&(var.perm_by_vol2))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"perm_by_vol2");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_coeff_type, field perm_by_vol2\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="concchan_coeff_type.dest";info.offset=(caddr_t)(&(var.dest))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"dest");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object concchan_coeff_type, field dest\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("concchan_coeff_type",fields);
}
void INFO_conserve_coeff_type(){
struct conserve_coeff_type var;Info info;char fields[2500];fields[0]='\0';info.name="conserve_coeff_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="conserve_coeff_type.pool";info.offset=(caddr_t)(&(var.pool))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"pool");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object conserve_coeff_type, field pool\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="conserve_coeff_type.tot";info.offset=(caddr_t)(&(var.tot))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"tot");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object conserve_coeff_type, field tot\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="conserve_coeff_type.init";info.offset=(caddr_t)(&(var.init))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"init");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object conserve_coeff_type, field init\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="conserve_coeff_type.num_others";info.offset=(caddr_t)(&(var.num_others))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_others");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object conserve_coeff_type, field num_others\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="conserve_coeff_type.others";info.offset=(caddr_t)(&(var.others))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"others");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object conserve_coeff_type, field others\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("conserve_coeff_type",fields);
}
void INFO_handle_msgins(){
struct handle_msgins var;Info info;char fields[2500];fields[0]='\0';info.name="handle_msgins";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="handle_msgins.clockno";info.offset=(caddr_t)(&(var.clockno))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"clockno");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field clockno\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgins.nexttime";info.offset=(caddr_t)(&(var.nexttime))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nexttime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field nexttime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgins.nmsgins";info.offset=(caddr_t)(&(var.nmsgins))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nmsgins");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field nmsgins\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgins.msgelm";info.offset=(caddr_t)(&(var.msgelm))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(2);InfoHashPut(&info);strcat(fields,"msgelm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field msgelm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgins.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="MsgIn";info.type_size=sizeof(MsgIn);__IFI(2);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgins.destpool";info.offset=(caddr_t)(&(var.destpool))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"destpool");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgins, field destpool\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("handle_msgins",fields);
}
void INFO_gsolve_type(){
struct gsolve_type var;Info info;char fields[2500];fields[0]='\0';info.name="gsolve_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="gsolve_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgdata";info.offset=(caddr_t)(&(var.msgdata))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"msgdata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgdata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.mirrormsgoffset";info.offset=(caddr_t)(&(var.mirrormsgoffset))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"mirrormsgoffset");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field mirrormsgoffset\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.msgcount";info.offset=(caddr_t)((var.msgcount))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IND(1);__IDS(0,8);InfoHashPut(&info);strcat(fields,"msgcount");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field msgcount\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.was_slaved";info.offset=(caddr_t)(&(var.was_slaved))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"was_slaved");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field was_slaved\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.oldmsgmode";info.offset=(caddr_t)(&(var.oldmsgmode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"oldmsgmode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field oldmsgmode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.reac_list";info.offset=(caddr_t)(&(var.reac_list))-(caddr_t)(&var);		info.type="ElementList";info.type_size=sizeof(ElementList);__IFI(1);InfoHashPut(&info);strcat(fields,"reac_list");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field reac_list\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.reac_list_populated";info.offset=(caddr_t)(&(var.reac_list_populated))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"reac_list_populated");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field reac_list_populated\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.enz_list";info.offset=(caddr_t)(&(var.enz_list))-(caddr_t)(&var);		info.type="ElementList";info.type_size=sizeof(ElementList);__IFI(1);InfoHashPut(&info);strcat(fields,"enz_list");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field enz_list\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.enz_list_populated";info.offset=(caddr_t)(&(var.enz_list_populated))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"enz_list_populated");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field enz_list_populated\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.pool_list";info.offset=(caddr_t)(&(var.pool_list))-(caddr_t)(&var);		info.type="ElementList";info.type_size=sizeof(ElementList);__IFI(1);InfoHashPut(&info);strcat(fields,"pool_list");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field pool_list\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.pool_list_populated";info.offset=(caddr_t)(&(var.pool_list_populated))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"pool_list_populated");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field pool_list_populated\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.sumtotal_list";info.offset=(caddr_t)(&(var.sumtotal_list))-(caddr_t)(&var);		info.type="ElementList";info.type_size=sizeof(ElementList);__IFI(1);InfoHashPut(&info);strcat(fields,"sumtotal_list");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field sumtotal_list\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.propensity_reac";info.offset=(caddr_t)((var.propensity_reac))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IND(2);__IDS(0,2);__IDS(1,500);InfoHashPut(&info);strcat(fields,"propensity_reac");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field propensity_reac\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.propensity_enz";info.offset=(caddr_t)((var.propensity_enz))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IND(2);__IDS(0,3);__IDS(1,300);InfoHashPut(&info);strcat(fields,"propensity_enz");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field propensity_enz\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.propensity_total";info.offset=(caddr_t)(&(var.propensity_total))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"propensity_total");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field propensity_total\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.internal_time";info.offset=(caddr_t)(&(var.internal_time))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"internal_time");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field internal_time\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="gsolve_type.method";info.offset=(caddr_t)(&(var.method))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"method");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object gsolve_type, field method\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("gsolve_type",fields);
}
void INFO_handle_msgouts(){
struct handle_msgouts var;Info info;char fields[2500];fields[0]='\0';info.name="handle_msgouts";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="handle_msgouts.clockno";info.offset=(caddr_t)(&(var.clockno))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"clockno");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field clockno\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgouts.nexttime";info.offset=(caddr_t)(&(var.nexttime))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nexttime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field nexttime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgouts.nmsgouts";info.offset=(caddr_t)(&(var.nmsgouts))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nmsgouts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field nmsgouts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgouts.msgelm";info.offset=(caddr_t)(&(var.msgelm))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(2);InfoHashPut(&info);strcat(fields,"msgelm");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field msgelm\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgouts.srcpool";info.offset=(caddr_t)(&(var.srcpool))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"srcpool");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field srcpool\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="handle_msgouts.isenz";info.offset=(caddr_t)(&(var.isenz))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"isenz");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object handle_msgouts, field isenz\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("handle_msgouts",fields);
}
void INFO_kentry_type(){
struct kentry_type var;Info info;char fields[2500];fields[0]='\0';info.name="kentry_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="kentry_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object kentry_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="kentry_type.coeff";info.offset=(caddr_t)(&(var.coeff))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"coeff");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object kentry_type, field coeff\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="kentry_type.pool";info.offset=(caddr_t)(&(var.pool))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"pool");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object kentry_type, field pool\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("kentry_type",fields);
}
void INFO_ksolve_type(){
struct ksolve_type var;Info info;char fields[2500];fields[0]='\0';info.name="ksolve_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="ksolve_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.currtime";info.offset=(caddr_t)(&(var.currtime))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"currtime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field currtime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.lasttime";info.offset=(caddr_t)(&(var.lasttime))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"lasttime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field lasttime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nextstep";info.offset=(caddr_t)(&(var.nextstep))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"nextstep");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nextstep\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.minstep";info.offset=(caddr_t)(&(var.minstep))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"minstep");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field minstep\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nok";info.offset=(caddr_t)(&(var.nok))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nok");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nok\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nbad";info.offset=(caddr_t)(&(var.nbad))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nbad");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nbad\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.vol";info.offset=(caddr_t)(&(var.vol))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"vol");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field vol\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.xtrapvector";info.offset=(caddr_t)(&(var.xtrapvector))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"xtrapvector");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field xtrapvector\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.xtrapmatrix";info.offset=(caddr_t)(&(var.xtrapmatrix))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"xtrapmatrix");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field xtrapmatrix\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.path";info.offset=(caddr_t)(&(var.path))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"path");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field path\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.method";info.offset=(caddr_t)(&(var.method))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"method");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field method\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.eps";info.offset=(caddr_t)(&(var.eps))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"eps");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field eps\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.elm_to_pointer";info.offset=(caddr_t)(&(var.elm_to_pointer))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"elm_to_pointer");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field elm_to_pointer\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.npools";info.offset=(caddr_t)(&(var.npools))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"npools");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field npools\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.pools";info.offset=(caddr_t)(&(var.pools))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"pools");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field pools\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.npoolcoeffs";info.offset=(caddr_t)(&(var.npoolcoeffs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"npoolcoeffs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field npoolcoeffs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.poolcoeffs";info.offset=(caddr_t)(&(var.poolcoeffs))-(caddr_t)(&var);		info.type="pool_coeff_type";info.type_size=sizeof(struct pool_coeff_type);__IFI(1);InfoHashPut(&info);strcat(fields,"poolcoeffs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field poolcoeffs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nreacs";info.offset=(caddr_t)(&(var.nreacs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nreacs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nreacs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.reacs";info.offset=(caddr_t)(&(var.reacs))-(caddr_t)(&var);		info.type="reac_coeff_type";info.type_size=sizeof(struct reac_coeff_type);__IFI(1);InfoHashPut(&info);strcat(fields,"reacs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field reacs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nenzs";info.offset=(caddr_t)(&(var.nenzs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nenzs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nenzs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.enzs";info.offset=(caddr_t)(&(var.enzs))-(caddr_t)(&var);		info.type="enz_coeff_type";info.type_size=sizeof(struct enz_coeff_type);__IFI(1);InfoHashPut(&info);strcat(fields,"enzs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field enzs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nconcchans";info.offset=(caddr_t)(&(var.nconcchans))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nconcchans");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nconcchans\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.concchans";info.offset=(caddr_t)(&(var.concchans))-(caddr_t)(&var);		info.type="concchan_coeff_type";info.type_size=sizeof(struct concchan_coeff_type);__IFI(1);InfoHashPut(&info);strcat(fields,"concchans");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field concchans\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nconsvs";info.offset=(caddr_t)(&(var.nconsvs))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nconsvs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nconsvs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nsumtots";info.offset=(caddr_t)(&(var.nsumtots))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nsumtots");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nsumtots\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.consvs";info.offset=(caddr_t)(&(var.consvs))-(caddr_t)(&var);		info.type="conserve_coeff_type";info.type_size=sizeof(struct conserve_coeff_type);__IFI(1);InfoHashPut(&info);strcat(fields,"consvs");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field consvs\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nslaves";info.offset=(caddr_t)(&(var.nslaves))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nslaves");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nslaves\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nmsgins";info.offset=(caddr_t)(&(var.nmsgins))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nmsgins");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nmsgins\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgins";info.offset=(caddr_t)(&(var.msgins))-(caddr_t)(&var);		info.type="handle_msgins";info.type_size=sizeof(struct handle_msgins);__IFI(1);InfoHashPut(&info);strcat(fields,"msgins");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgins\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nmsgouts";info.offset=(caddr_t)(&(var.nmsgouts))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nmsgouts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nmsgouts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.msgouts";info.offset=(caddr_t)(&(var.msgouts))-(caddr_t)(&var);		info.type="handle_msgouts";info.type_size=sizeof(struct handle_msgouts);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouts");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field msgouts\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.nkentries";info.offset=(caddr_t)(&(var.nkentries))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nkentries");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field nkentries\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ksolve_type.kentries";info.offset=(caddr_t)(&(var.kentries))-(caddr_t)(&var);		info.type="kentry_type";info.type_size=sizeof(struct kentry_type);__IFI(1);InfoHashPut(&info);strcat(fields,"kentries");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ksolve_type, field kentries\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("ksolve_type",fields);
}
void INFO_text_type(){
struct text_type var;Info info;char fields[2500];fields[0]='\0';info.name="text_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="text_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.str";info.offset=(caddr_t)(&(var.str))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"str");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field str\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="text_type.len";info.offset=(caddr_t)(&(var.len))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"len");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object text_type, field len\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("text_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_kin(){
INFO_pool_type();
INFO_reac_type();
INFO_enz_type();
INFO_concchan_type();
INFO_pool_coeff_type();
INFO_reac_coeff_type();
INFO_enz_coeff_type();
INFO_concchan_coeff_type();
INFO_conserve_coeff_type();
INFO_handle_msgins();
INFO_gsolve_type();
INFO_handle_msgouts();
INFO_kentry_type();
INFO_ksolve_type();
INFO_text_type();
}
