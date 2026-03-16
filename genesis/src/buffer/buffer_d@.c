#include "buf_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_variable_type(){
struct variable_type var;Info info;char fields[2500];fields[0]='\0';info.name="variable_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="variable_type.value";info.offset=(caddr_t)(&(var.value))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"value");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object variable_type, field value\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("variable_type",fields);
}
void INFO_random_type(){
struct random_type var;Info info;char fields[2500];fields[0]='\0';info.name="random_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="random_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.rate";info.offset=(caddr_t)(&(var.rate))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"rate");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field rate\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.max_amp";info.offset=(caddr_t)(&(var.max_amp))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"max_amp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field max_amp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.min_amp";info.offset=(caddr_t)(&(var.min_amp))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"min_amp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field min_amp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.reset";info.offset=(caddr_t)(&(var.reset))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"reset");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field reset\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="random_type.reset_value";info.offset=(caddr_t)(&(var.reset_value))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"reset_value");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object random_type, field reset_value\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("random_type",fields);
}
void INFO_playback_type(){
struct playback_type var;Info info;char fields[2500];fields[0]='\0';info.name="playback_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="playback_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="playback_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object playback_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("playback_type",fields);
}
void INFO_periodic_type(){
struct periodic_type var;Info info;char fields[2500];fields[0]='\0';info.name="periodic_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="periodic_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.stime";info.offset=(caddr_t)(&(var.stime))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"stime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field stime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="periodic_type.mode";info.offset=(caddr_t)(&(var.mode))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"mode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object periodic_type, field mode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("periodic_type",fields);
}
void INFO_spike_type(){
struct spike_type var;Info info;char fields[2500];fields[0]='\0';info.name="spike_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="spike_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.thresh";info.offset=(caddr_t)(&(var.thresh))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"thresh");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field thresh\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.abs_refract";info.offset=(caddr_t)(&(var.abs_refract))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"abs_refract");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field abs_refract\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spike_type.output_amp";info.offset=(caddr_t)(&(var.output_amp))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"output_amp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spike_type, field output_amp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("spike_type",fields);
}
void INFO_state_type(){
struct state_type var;Info info;char fields[2500];fields[0]='\0';info.name="state_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="state_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="state_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object state_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("state_type",fields);
}
void INFO_graded_type(){
struct graded_type var;Info info;char fields[2500];fields[0]='\0';info.name="graded_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="graded_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.baseline";info.offset=(caddr_t)(&(var.baseline))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"baseline");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field baseline\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="graded_type.rectify";info.offset=(caddr_t)(&(var.rectify))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"rectify");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object graded_type, field rectify\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("graded_type",fields);
}
void INFO_sigmoid_type(){
struct sigmoid_type var;Info info;char fields[2500];fields[0]='\0';info.name="sigmoid_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="sigmoid_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.input";info.offset=(caddr_t)(&(var.input))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"input");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field input\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.gain";info.offset=(caddr_t)(&(var.gain))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"gain");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field gain\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.amplitude";info.offset=(caddr_t)(&(var.amplitude))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"amplitude");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field amplitude\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="sigmoid_type.thresh";info.offset=(caddr_t)(&(var.thresh))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"thresh");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object sigmoid_type, field thresh\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("sigmoid_type",fields);
}
void INFO_linear_type(){
struct linear_type var;Info info;char fields[2500];fields[0]='\0';info.name="linear_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="linear_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.gain";info.offset=(caddr_t)(&(var.gain))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"gain");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field gain\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="linear_type.thresh";info.offset=(caddr_t)(&(var.thresh))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"thresh");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object linear_type, field thresh\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("linear_type",fields);
}
void INFO_inject_type(){
struct inject_type var;Info info;char fields[2500];fields[0]='\0';info.name="inject_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="inject_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="inject_type.inject";info.offset=(caddr_t)(&(var.inject))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"inject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object inject_type, field inject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("inject_type",fields);
}
void INFO_passive_type(){
struct passive_type var;Info info;char fields[2500];fields[0]='\0';info.name="passive_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="passive_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.tmin";info.offset=(caddr_t)(&(var.tmin))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"tmin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field tmin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.size";info.offset=(caddr_t)(&(var.size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.current";info.offset=(caddr_t)(&(var.current))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"current");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field current\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.start";info.offset=(caddr_t)(&(var.start))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"start");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field start\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.end";info.offset=(caddr_t)(&(var.end))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"end");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field end\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.event_size";info.offset=(caddr_t)(&(var.event_size))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"event_size");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field event_size\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="passive_type.event";info.offset=(caddr_t)(&(var.event))-(caddr_t)(&var);		info.type="event_type";info.type_size=sizeof(struct event_type);__IFI(1);InfoHashPut(&info);strcat(fields,"event");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object passive_type, field event\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("passive_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_buffer(){
INFO_variable_type();
INFO_random_type();
INFO_playback_type();
INFO_periodic_type();
INFO_spike_type();
INFO_state_type();
INFO_graded_type();
INFO_sigmoid_type();
INFO_linear_type();
INFO_inject_type();
INFO_passive_type();
}
