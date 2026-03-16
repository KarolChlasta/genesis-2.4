#include "param_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_paramtableBF_type(){
struct paramtableBF_type var;Info info;char fields[2500];fields[0]='\0';info.name="paramtableBF_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="paramtableBF_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.iteration_number";info.offset=(caddr_t)(&(var.iteration_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"iteration_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field iteration_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.num_params";info.offset=(caddr_t)(&(var.num_params))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field num_params\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.num_params_to_search";info.offset=(caddr_t)(&(var.num_params_to_search))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params_to_search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field num_params_to_search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.search";info.offset=(caddr_t)(&(var.search))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.range";info.offset=(caddr_t)(&(var.range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.min";info.offset=(caddr_t)(&(var.min))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"min");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field min\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.max";info.offset=(caddr_t)(&(var.max))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"max");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field max\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.label";info.offset=(caddr_t)(&(var.label))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"label");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field label\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.current_match";info.offset=(caddr_t)(&(var.current_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"current_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field current_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.best";info.offset=(caddr_t)(&(var.best))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"best");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field best\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.best_match";info.offset=(caddr_t)(&(var.best_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.new_best_match";info.offset=(caddr_t)(&(var.new_best_match))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"new_best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field new_best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.done";info.offset=(caddr_t)(&(var.done))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"done");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field done\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.alloced";info.offset=(caddr_t)(&(var.alloced))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"alloced");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field alloced\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.orig";info.offset=(caddr_t)(&(var.orig))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"orig");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field orig\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.search_divisions";info.offset=(caddr_t)(&(var.search_divisions))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"search_divisions");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field search_divisions\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.search_rangemod";info.offset=(caddr_t)(&(var.search_rangemod))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"search_rangemod");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field search_rangemod\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.search_count";info.offset=(caddr_t)(&(var.search_count))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"search_count");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field search_count\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableBF_type.search_range";info.offset=(caddr_t)(&(var.search_range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"search_range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableBF_type, field search_range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("paramtableBF_type",fields);
}
void INFO_paramtableCG_type(){
struct paramtableCG_type var;Info info;char fields[2500];fields[0]='\0';info.name="paramtableCG_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="paramtableCG_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.iteration_number";info.offset=(caddr_t)(&(var.iteration_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"iteration_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field iteration_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.num_params";info.offset=(caddr_t)(&(var.num_params))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field num_params\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.num_params_to_search";info.offset=(caddr_t)(&(var.num_params_to_search))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params_to_search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field num_params_to_search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.search";info.offset=(caddr_t)(&(var.search))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.center";info.offset=(caddr_t)(&(var.center))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"center");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field center\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.realcenter";info.offset=(caddr_t)(&(var.realcenter))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realcenter");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field realcenter\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.range";info.offset=(caddr_t)(&(var.range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.realrange";info.offset=(caddr_t)(&(var.realrange))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realrange");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field realrange\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.min";info.offset=(caddr_t)(&(var.min))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"min");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field min\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.realmin";info.offset=(caddr_t)(&(var.realmin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field realmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.max";info.offset=(caddr_t)(&(var.max))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"max");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field max\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.realmax";info.offset=(caddr_t)(&(var.realmax))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field realmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.label";info.offset=(caddr_t)(&(var.label))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"label");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field label\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.realcurrent";info.offset=(caddr_t)(&(var.realcurrent))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realcurrent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field realcurrent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.current_match";info.offset=(caddr_t)(&(var.current_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"current_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field current_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.best";info.offset=(caddr_t)(&(var.best))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"best");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field best\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.best_match";info.offset=(caddr_t)(&(var.best_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.new_best_match";info.offset=(caddr_t)(&(var.new_best_match))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"new_best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field new_best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.done";info.offset=(caddr_t)(&(var.done))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"done");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field done\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.alloced";info.offset=(caddr_t)(&(var.alloced))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"alloced");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field alloced\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_number";info.offset=(caddr_t)(&(var.linemin_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"linemin_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_method";info.offset=(caddr_t)(&(var.deriv_method))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"deriv_method");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_method\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.orig_param";info.offset=(caddr_t)(&(var.orig_param))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"orig_param");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field orig_param\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.h";info.offset=(caddr_t)(&(var.h))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"h");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field h\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.h_init";info.offset=(caddr_t)(&(var.h_init))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"h_init");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field h_init\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_count";info.offset=(caddr_t)(&(var.deriv_count))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"deriv_count");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_count\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_state";info.offset=(caddr_t)(&(var.deriv_state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"deriv_state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_index";info.offset=(caddr_t)(&(var.deriv_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"deriv_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_h_init";info.offset=(caddr_t)(&(var.deriv_h_init))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"deriv_h_init");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_h_init\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_h_decrease";info.offset=(caddr_t)(&(var.deriv_h_decrease))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"deriv_h_decrease");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_h_decrease\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_h_min";info.offset=(caddr_t)(&(var.deriv_h_min))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"deriv_h_min");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_h_min\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv_matrix";info.offset=(caddr_t)(&(var.deriv_matrix))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"deriv_matrix");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv_matrix\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.deriv";info.offset=(caddr_t)(&(var.deriv))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"deriv");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field deriv\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.g";info.offset=(caddr_t)(&(var.g))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"g");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field g\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.dir";info.offset=(caddr_t)(&(var.dir))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"dir");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field dir\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.tolerance";info.offset=(caddr_t)(&(var.tolerance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"tolerance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field tolerance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_state";info.offset=(caddr_t)(&(var.linemin_state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"linemin_state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_init";info.offset=(caddr_t)(&(var.linemin_init))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"linemin_init");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_init\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_bracket_state";info.offset=(caddr_t)(&(var.linemin_bracket_state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"linemin_bracket_state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_bracket_state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_bracket";info.offset=(caddr_t)(&(var.linemin_bracket))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"linemin_bracket");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_bracket\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_mbracket";info.offset=(caddr_t)(&(var.linemin_mbracket))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"linemin_mbracket");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_mbracket\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_brent_state";info.offset=(caddr_t)(&(var.linemin_brent_state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"linemin_brent_state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_brent_state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_point";info.offset=(caddr_t)(&(var.linemin_point))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"linemin_point");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_point\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_match";info.offset=(caddr_t)(&(var.linemin_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"linemin_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.prev_linemin_match";info.offset=(caddr_t)(&(var.prev_linemin_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"prev_linemin_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field prev_linemin_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_origin";info.offset=(caddr_t)(&(var.linemin_origin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"linemin_origin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_origin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableCG_type.linemin_tolerance";info.offset=(caddr_t)(&(var.linemin_tolerance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"linemin_tolerance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableCG_type, field linemin_tolerance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("paramtableCG_type",fields);
}
void INFO_paramtableGA_type(){
struct paramtableGA_type var;Info info;char fields[2500];fields[0]='\0';info.name="paramtableGA_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="paramtableGA_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.generation";info.offset=(caddr_t)(&(var.generation))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"generation");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field generation\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.num_tables";info.offset=(caddr_t)(&(var.num_tables))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_tables");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field num_tables\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.num_params";info.offset=(caddr_t)(&(var.num_params))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field num_params\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.num_params_to_search";info.offset=(caddr_t)(&(var.num_params_to_search))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params_to_search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field num_params_to_search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.search";info.offset=(caddr_t)(&(var.search))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.center";info.offset=(caddr_t)(&(var.center))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"center");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field center\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.range";info.offset=(caddr_t)(&(var.range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.label";info.offset=(caddr_t)(&(var.label))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"label");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field label\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.best";info.offset=(caddr_t)(&(var.best))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"best");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field best\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.best_match";info.offset=(caddr_t)(&(var.best_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.alloced";info.offset=(caddr_t)(&(var.alloced))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"alloced");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field alloced\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.param_size";info.offset=(caddr_t)(&(var.param_size))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"param_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field param_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.bits_per_parameter";info.offset=(caddr_t)(&(var.bits_per_parameter))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"bits_per_parameter");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field bits_per_parameter\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.max_parameter";info.offset=(caddr_t)(&(var.max_parameter))-(caddr_t)(&var);		info.type="Param_long";info.type_size=sizeof(Param_long);InfoHashPut(&info);strcat(fields,"max_parameter");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field max_parameter\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.param";info.offset=(caddr_t)(&(var.param))-(caddr_t)(&var);		info.type="Param";info.type_size=sizeof(Param);__IFI(2);InfoHashPut(&info);strcat(fields,"param");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field param\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.temp";info.offset=(caddr_t)(&(var.temp))-(caddr_t)(&var);		info.type="Param";info.type_size=sizeof(Param);__IFI(2);InfoHashPut(&info);strcat(fields,"temp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field temp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.fitness";info.offset=(caddr_t)(&(var.fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.tempfitness";info.offset=(caddr_t)(&(var.tempfitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"tempfitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field tempfitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.fitrank";info.offset=(caddr_t)(&(var.fitrank))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"fitrank");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field fitrank\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.min_fitness";info.offset=(caddr_t)(&(var.min_fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"min_fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field min_fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.max_fitness";info.offset=(caddr_t)(&(var.max_fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"max_fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field max_fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.avg_fitness";info.offset=(caddr_t)(&(var.avg_fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"avg_fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field avg_fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.stdev_fitness";info.offset=(caddr_t)(&(var.stdev_fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"stdev_fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field stdev_fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.min_fitness_index";info.offset=(caddr_t)(&(var.min_fitness_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"min_fitness_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field min_fitness_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.max_fitness_index";info.offset=(caddr_t)(&(var.max_fitness_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"max_fitness_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field max_fitness_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.normfitness";info.offset=(caddr_t)(&(var.normfitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"normfitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field normfitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.cumulfitness";info.offset=(caddr_t)(&(var.cumulfitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"cumulfitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field cumulfitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.selectindex";info.offset=(caddr_t)(&(var.selectindex))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);__IFI(1);InfoHashPut(&info);strcat(fields,"selectindex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field selectindex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.preserve";info.offset=(caddr_t)(&(var.preserve))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"preserve");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field preserve\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.crossover_type";info.offset=(caddr_t)(&(var.crossover_type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"crossover_type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field crossover_type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.crossover_probability";info.offset=(caddr_t)(&(var.crossover_probability))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"crossover_probability");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field crossover_probability\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.crossover_number";info.offset=(caddr_t)(&(var.crossover_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"crossover_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field crossover_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.crossover_break_param";info.offset=(caddr_t)(&(var.crossover_break_param))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"crossover_break_param");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field crossover_break_param\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.mutation_probability";info.offset=(caddr_t)(&(var.mutation_probability))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"mutation_probability");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field mutation_probability\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.use_gray_code";info.offset=(caddr_t)(&(var.use_gray_code))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"use_gray_code");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field use_gray_code\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.do_restart";info.offset=(caddr_t)(&(var.do_restart))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"do_restart");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field do_restart\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.restart_after";info.offset=(caddr_t)(&(var.restart_after))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"restart_after");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field restart_after\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.restart_count";info.offset=(caddr_t)(&(var.restart_count))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"restart_count");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field restart_count\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.old_fitness";info.offset=(caddr_t)(&(var.old_fitness))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"old_fitness");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field old_fitness\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableGA_type.restart_thresh";info.offset=(caddr_t)(&(var.restart_thresh))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"restart_thresh");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableGA_type, field restart_thresh\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("paramtableGA_type",fields);
}
void INFO_paramtableSA_type(){
struct paramtableSA_type var;Info info;char fields[2500];fields[0]='\0';info.name="paramtableSA_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="paramtableSA_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.iteration_number";info.offset=(caddr_t)(&(var.iteration_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"iteration_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field iteration_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.num_params";info.offset=(caddr_t)(&(var.num_params))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field num_params\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.num_params_to_search";info.offset=(caddr_t)(&(var.num_params_to_search))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params_to_search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field num_params_to_search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.search";info.offset=(caddr_t)(&(var.search))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.center";info.offset=(caddr_t)(&(var.center))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"center");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field center\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.realcenter";info.offset=(caddr_t)(&(var.realcenter))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realcenter");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field realcenter\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.range";info.offset=(caddr_t)(&(var.range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.realrange";info.offset=(caddr_t)(&(var.realrange))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realrange");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field realrange\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.min";info.offset=(caddr_t)(&(var.min))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"min");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field min\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.realmin";info.offset=(caddr_t)(&(var.realmin))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field realmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.max";info.offset=(caddr_t)(&(var.max))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"max");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field max\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.realmax";info.offset=(caddr_t)(&(var.realmax))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"realmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field realmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.label";info.offset=(caddr_t)(&(var.label))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"label");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field label\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.current_match";info.offset=(caddr_t)(&(var.current_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"current_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field current_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.best";info.offset=(caddr_t)(&(var.best))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"best");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field best\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.best_match";info.offset=(caddr_t)(&(var.best_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.best_match_iteration";info.offset=(caddr_t)(&(var.best_match_iteration))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"best_match_iteration");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field best_match_iteration\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.new_best_match";info.offset=(caddr_t)(&(var.new_best_match))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"new_best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field new_best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.done";info.offset=(caddr_t)(&(var.done))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"done");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field done\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.alloced";info.offset=(caddr_t)(&(var.alloced))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"alloced");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field alloced\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.iterations_per_temp";info.offset=(caddr_t)(&(var.iterations_per_temp))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"iterations_per_temp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field iterations_per_temp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.temperature";info.offset=(caddr_t)(&(var.temperature))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"temperature");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field temperature\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.inittemp";info.offset=(caddr_t)(&(var.inittemp))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"inittemp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field inittemp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.annealing_method";info.offset=(caddr_t)(&(var.annealing_method))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"annealing_method");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field annealing_method\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.max_iterations";info.offset=(caddr_t)(&(var.max_iterations))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"max_iterations");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field max_iterations\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.annealing_rate";info.offset=(caddr_t)(&(var.annealing_rate))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"annealing_rate");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field annealing_rate\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.testtemp";info.offset=(caddr_t)(&(var.testtemp))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"testtemp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field testtemp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.tolerance";info.offset=(caddr_t)(&(var.tolerance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"tolerance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field tolerance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.stop_after";info.offset=(caddr_t)(&(var.stop_after))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"stop_after");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field stop_after\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.restart_every";info.offset=(caddr_t)(&(var.restart_every))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"restart_every");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field restart_every\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.next_index";info.offset=(caddr_t)(&(var.next_index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"next_index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field next_index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.simplex_init_noise";info.offset=(caddr_t)(&(var.simplex_init_noise))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"simplex_init_noise");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field simplex_init_noise\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.simplex";info.offset=(caddr_t)(&(var.simplex))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(2);InfoHashPut(&info);strcat(fields,"simplex");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field simplex\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.simplex_match";info.offset=(caddr_t)(&(var.simplex_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"simplex_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field simplex_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.partial_sum";info.offset=(caddr_t)(&(var.partial_sum))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"partial_sum");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field partial_sum\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.test_point";info.offset=(caddr_t)(&(var.test_point))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"test_point");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field test_point\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSA_type.scalemod";info.offset=(caddr_t)(&(var.scalemod))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"scalemod");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSA_type, field scalemod\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("paramtableSA_type",fields);
}
void INFO_paramtableSS_type(){
struct paramtableSS_type var;Info info;char fields[2500];fields[0]='\0';info.name="paramtableSS_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="paramtableSS_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.iteration_number";info.offset=(caddr_t)(&(var.iteration_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"iteration_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field iteration_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.num_params";info.offset=(caddr_t)(&(var.num_params))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"num_params");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field num_params\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.search";info.offset=(caddr_t)(&(var.search))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"search");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field search\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.type";info.offset=(caddr_t)(&(var.type))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);__IFI(1);InfoHashPut(&info);strcat(fields,"type");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field type\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.range";info.offset=(caddr_t)(&(var.range))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"range");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field range\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.min";info.offset=(caddr_t)(&(var.min))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"min");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field min\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.max";info.offset=(caddr_t)(&(var.max))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"max");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field max\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.label";info.offset=(caddr_t)(&(var.label))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"label");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field label\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.best";info.offset=(caddr_t)(&(var.best))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"best");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field best\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.best_match";info.offset=(caddr_t)(&(var.best_match))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"best_match");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field best_match\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.alloced";info.offset=(caddr_t)(&(var.alloced))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"alloced");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field alloced\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.round_number";info.offset=(caddr_t)(&(var.round_number))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"round_number");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field round_number\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.variance";info.offset=(caddr_t)(&(var.variance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"variance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field variance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.minvariance";info.offset=(caddr_t)(&(var.minvariance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"minvariance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field minvariance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.maxvariance";info.offset=(caddr_t)(&(var.maxvariance))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"maxvariance");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field maxvariance\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.addvarscale";info.offset=(caddr_t)(&(var.addvarscale))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"addvarscale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field addvarscale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.multvarscale";info.offset=(caddr_t)(&(var.multvarscale))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"multvarscale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field multvarscale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="paramtableSS_type.contract";info.offset=(caddr_t)(&(var.contract))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"contract");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object paramtableSS_type, field contract\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("paramtableSS_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_param(){
INFO_paramtableBF_type();
INFO_paramtableCG_type();
INFO_paramtableGA_type();
INFO_paramtableSA_type();
INFO_paramtableSS_type();
}
