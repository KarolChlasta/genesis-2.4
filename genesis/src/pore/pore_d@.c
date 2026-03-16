#include "pore_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_K_pore_type(){
struct K_pore_type var;Info info;char fields[2500];fields[0]='\0';info.name="K_pore_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="K_pore_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.activation";info.offset=(caddr_t)(&(var.activation))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"activation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field activation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Vk";info.offset=(caddr_t)(&(var.Vk))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Vk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Vk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Ek";info.offset=(caddr_t)(&(var.Ek))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ek");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Ek\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Ik";info.offset=(caddr_t)(&(var.Ik))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ik");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Ik\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Gk";info.offset=(caddr_t)(&(var.Gk))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Gk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Gk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Gmax";info.offset=(caddr_t)(&(var.Gmax))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Gmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Gmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.Nt";info.offset=(caddr_t)(&(var.Nt))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"Nt");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field Nt\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.No";info.offset=(caddr_t)(&(var.No))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"No");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field No\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.n0";info.offset=(caddr_t)(&(var.n0))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"n0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field n0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.n1";info.offset=(caddr_t)(&(var.n1))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"n1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field n1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.n2";info.offset=(caddr_t)(&(var.n2))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"n2");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field n2\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.n3";info.offset=(caddr_t)(&(var.n3))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"n3");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field n3\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.n4";info.offset=(caddr_t)(&(var.n4))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"n4");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field n4\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.alpha_A";info.offset=(caddr_t)(&(var.alpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field alpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.alpha_B";info.offset=(caddr_t)(&(var.alpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field alpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.alpha_C";info.offset=(caddr_t)(&(var.alpha_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field alpha_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.alpha_D";info.offset=(caddr_t)(&(var.alpha_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field alpha_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.alpha_F";info.offset=(caddr_t)(&(var.alpha_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"alpha_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field alpha_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.beta_A";info.offset=(caddr_t)(&(var.beta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field beta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.beta_B";info.offset=(caddr_t)(&(var.beta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field beta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.beta_C";info.offset=(caddr_t)(&(var.beta_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field beta_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.beta_D";info.offset=(caddr_t)(&(var.beta_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field beta_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="K_pore_type.beta_F";info.offset=(caddr_t)(&(var.beta_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"beta_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object K_pore_type, field beta_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("K_pore_type",fields);
}
void INFO_Na_pore_type(){
struct Na_pore_type var;Info info;char fields[2500];fields[0]='\0';info.name="Na_pore_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="Na_pore_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.activation";info.offset=(caddr_t)(&(var.activation))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"activation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field activation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Vk";info.offset=(caddr_t)(&(var.Vk))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Vk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Vk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Ek";info.offset=(caddr_t)(&(var.Ek))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ek");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Ek\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Ik";info.offset=(caddr_t)(&(var.Ik))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Ik");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Ik\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Gk";info.offset=(caddr_t)(&(var.Gk))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"Gk");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Gk\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Gmax";info.offset=(caddr_t)(&(var.Gmax))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"Gmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Gmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.Nt";info.offset=(caddr_t)(&(var.Nt))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"Nt");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field Nt\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.No";info.offset=(caddr_t)(&(var.No))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"No");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field No\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m0h0";info.offset=(caddr_t)(&(var.m0h0))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m0h0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m0h0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m1h0";info.offset=(caddr_t)(&(var.m1h0))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m1h0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m1h0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m2h0";info.offset=(caddr_t)(&(var.m2h0))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m2h0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m2h0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m3h0";info.offset=(caddr_t)(&(var.m3h0))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m3h0");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m3h0\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m0h1";info.offset=(caddr_t)(&(var.m0h1))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m0h1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m0h1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m1h1";info.offset=(caddr_t)(&(var.m1h1))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m1h1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m1h1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m2h1";info.offset=(caddr_t)(&(var.m2h1))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m2h1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m2h1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.m3h1";info.offset=(caddr_t)(&(var.m3h1))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"m3h1");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field m3h1\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.malpha_A";info.offset=(caddr_t)(&(var.malpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"malpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field malpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.malpha_B";info.offset=(caddr_t)(&(var.malpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"malpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field malpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.malpha_C";info.offset=(caddr_t)(&(var.malpha_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"malpha_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field malpha_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.malpha_D";info.offset=(caddr_t)(&(var.malpha_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"malpha_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field malpha_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.malpha_F";info.offset=(caddr_t)(&(var.malpha_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"malpha_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field malpha_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.mbeta_A";info.offset=(caddr_t)(&(var.mbeta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"mbeta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field mbeta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.mbeta_B";info.offset=(caddr_t)(&(var.mbeta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"mbeta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field mbeta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.mbeta_C";info.offset=(caddr_t)(&(var.mbeta_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"mbeta_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field mbeta_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.mbeta_D";info.offset=(caddr_t)(&(var.mbeta_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"mbeta_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field mbeta_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.mbeta_F";info.offset=(caddr_t)(&(var.mbeta_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"mbeta_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field mbeta_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.halpha_A";info.offset=(caddr_t)(&(var.halpha_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"halpha_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field halpha_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.halpha_B";info.offset=(caddr_t)(&(var.halpha_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"halpha_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field halpha_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.halpha_C";info.offset=(caddr_t)(&(var.halpha_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"halpha_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field halpha_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.halpha_D";info.offset=(caddr_t)(&(var.halpha_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"halpha_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field halpha_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.halpha_F";info.offset=(caddr_t)(&(var.halpha_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"halpha_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field halpha_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.hbeta_A";info.offset=(caddr_t)(&(var.hbeta_A))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"hbeta_A");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field hbeta_A\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.hbeta_B";info.offset=(caddr_t)(&(var.hbeta_B))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"hbeta_B");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field hbeta_B\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.hbeta_C";info.offset=(caddr_t)(&(var.hbeta_C))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"hbeta_C");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field hbeta_C\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.hbeta_D";info.offset=(caddr_t)(&(var.hbeta_D))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"hbeta_D");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field hbeta_D\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="Na_pore_type.hbeta_F";info.offset=(caddr_t)(&(var.hbeta_F))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"hbeta_F");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object Na_pore_type, field hbeta_F\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("Na_pore_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_pore(){
INFO_K_pore_type();
INFO_Na_pore_type();
}
