#include "hh_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_vdep_gate_type(){
struct vdep_gate_type var;Info info;char fields[2500];fields[0]='\0';info.name="vdep_gate_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="vdep_gate_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.activation";info.offset=(caddr_t)(&(var.activation))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"activation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field activation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.m";info.offset=(caddr_t)(&(var.m))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"m");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field m\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.alpha_A";info.offset=(caddr_t)(&(var.alpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field alpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.alpha_B";info.offset=(caddr_t)(&(var.alpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field alpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.alpha_C";info.offset=(caddr_t)(&(var.alpha_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field alpha_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.alpha_D";info.offset=(caddr_t)(&(var.alpha_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field alpha_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.alpha_F";info.offset=(caddr_t)(&(var.alpha_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field alpha_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.beta_A";info.offset=(caddr_t)(&(var.beta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field beta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.beta_B";info.offset=(caddr_t)(&(var.beta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field beta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.beta_C";info.offset=(caddr_t)(&(var.beta_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field beta_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.beta_D";info.offset=(caddr_t)(&(var.beta_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field beta_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.beta_F";info.offset=(caddr_t)(&(var.beta_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field beta_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_gate_type.instantaneous";info.offset=(caddr_t)(&(var.instantaneous))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"instantaneous");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_gate_type, field instantaneous\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("vdep_gate_type",fields);
}
void INFO_vdep_channel_type(){
struct vdep_channel_type var;Info info;char fields[2500];fields[0]='\0';info.name="vdep_channel_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="vdep_channel_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.activation";info.offset=(caddr_t)(&(var.activation))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"activation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field activation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.Ik";info.offset=(caddr_t)(&(var.Ik))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Ik");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field Ik\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.Gk";info.offset=(caddr_t)(&(var.Gk))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Gk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field Gk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.Ek";info.offset=(caddr_t)(&(var.Ek))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ek");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field Ek\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="vdep_channel_type.gbar";info.offset=(caddr_t)(&(var.gbar))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"gbar");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object vdep_channel_type, field gbar\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("vdep_channel_type",fields);
}
void INFO_hh_channel_type(){
struct hh_channel_type var;Info info;char fields[2500];fields[0]='\0';info.name="hh_channel_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="hh_channel_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.activation";info.offset=(caddr_t)(&(var.activation))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"activation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field activation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Ik";info.offset=(caddr_t)(&(var.Ik))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Ik");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Ik\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Gk";info.offset=(caddr_t)(&(var.Gk))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Gk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Gk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Ek";info.offset=(caddr_t)(&(var.Ek))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ek");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Ek\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Gbar";info.offset=(caddr_t)(&(var.Gbar))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Gbar");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Gbar\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X";info.offset=(caddr_t)(&(var.X))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"X");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y";info.offset=(caddr_t)(&(var.Y))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Xpower";info.offset=(caddr_t)(&(var.Xpower))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Xpower");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Xpower\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Ypower";info.offset=(caddr_t)(&(var.Ypower))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ypower");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Ypower\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_alpha_FORM";info.offset=(caddr_t)(&(var.X_alpha_FORM))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"X_alpha_FORM");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_alpha_FORM\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_alpha_A";info.offset=(caddr_t)(&(var.X_alpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_alpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_alpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_alpha_B";info.offset=(caddr_t)(&(var.X_alpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_alpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_alpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_alpha_V0";info.offset=(caddr_t)(&(var.X_alpha_V0))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_alpha_V0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_alpha_V0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_beta_FORM";info.offset=(caddr_t)(&(var.X_beta_FORM))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"X_beta_FORM");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_beta_FORM\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_beta_A";info.offset=(caddr_t)(&(var.X_beta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_beta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_beta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_beta_B";info.offset=(caddr_t)(&(var.X_beta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_beta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_beta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.X_beta_V0";info.offset=(caddr_t)(&(var.X_beta_V0))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"X_beta_V0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field X_beta_V0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_alpha_FORM";info.offset=(caddr_t)(&(var.Y_alpha_FORM))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"Y_alpha_FORM");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_alpha_FORM\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_alpha_A";info.offset=(caddr_t)(&(var.Y_alpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_alpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_alpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_alpha_B";info.offset=(caddr_t)(&(var.Y_alpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_alpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_alpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_alpha_V0";info.offset=(caddr_t)(&(var.Y_alpha_V0))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_alpha_V0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_alpha_V0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_beta_FORM";info.offset=(caddr_t)(&(var.Y_beta_FORM))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"Y_beta_FORM");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_beta_FORM\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_beta_A";info.offset=(caddr_t)(&(var.Y_beta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_beta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_beta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_beta_B";info.offset=(caddr_t)(&(var.Y_beta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_beta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_beta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="hh_channel_type.Y_beta_V0";info.offset=(caddr_t)(&(var.Y_beta_V0))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Y_beta_V0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object hh_channel_type, field Y_beta_V0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("hh_channel_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_hh(){
INFO_vdep_gate_type();
INFO_vdep_channel_type();
INFO_hh_channel_type();
}
