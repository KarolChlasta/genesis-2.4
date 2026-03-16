#include "out_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_output_data_type(){
struct output_data_type var;Info info;char fields[2500];fields[0]='\0';info.name="output_data_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="output_data_type.element";info.offset=(caddr_t)(&(var.element))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"element");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field element\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.dataptr";info.offset=(caddr_t)(&(var.dataptr))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);__IFI(1);InfoHashPut(&info);strcat(fields,"dataptr");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field dataptr\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.datatype";info.offset=(caddr_t)(&(var.datatype))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datatype");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field datatype\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.datasize";info.offset=(caddr_t)(&(var.datasize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datasize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field datasize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.data_func";info.offset=(caddr_t)(&(var.data_func))-(caddr_t)(&var);		info.type="PFI";info.type_size=sizeof(PFI);__IFT;InfoHashPut(&info);strcat(fields,"data_func");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field data_func\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_data_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="output_data_type";info.type_size=sizeof(struct output_data_type);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_data_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("output_data_type",fields);
}
void INFO_output_type(){
struct output_type var;Info info;char fields[2500];fields[0]='\0';info.name="output_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="output_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.datatype";info.offset=(caddr_t)(&(var.datatype))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datatype");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field datatype\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.datasize";info.offset=(caddr_t)(&(var.datasize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datasize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field datasize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.mixed_data";info.offset=(caddr_t)(&(var.mixed_data))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"mixed_data");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field mixed_data\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="output_type.data";info.offset=(caddr_t)(&(var.data))-(caddr_t)(&var);		info.type="output_data_type";info.type_size=sizeof(struct output_data_type);__IFI(1);InfoHashPut(&info);strcat(fields,"data");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object output_type, field data\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("output_type",fields);
}
void INFO_file_type(){
struct file_type var;Info info;char fields[2500];fields[0]='\0';info.name="file_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="file_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.fp";info.offset=(caddr_t)(&(var.fp))-(caddr_t)(&var);		info.type="FILE";info.type_size=sizeof(FILE);__IFI(1);InfoHashPut(&info);strcat(fields,"fp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field fp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.is_open";info.offset=(caddr_t)(&(var.is_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"is_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field is_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.initialize";info.offset=(caddr_t)(&(var.initialize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"initialize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field initialize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.leave_open";info.offset=(caddr_t)(&(var.leave_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"leave_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field leave_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.append";info.offset=(caddr_t)(&(var.append))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"append");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field append\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="file_type.flush";info.offset=(caddr_t)(&(var.flush))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flush");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object file_type, field flush\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("file_type",fields);
}
void INFO_xviewfile_type(){
struct xviewfile_type var;Info info;char fields[2500];fields[0]='\0';info.name="xviewfile_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="xviewfile_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.fp";info.offset=(caddr_t)(&(var.fp))-(caddr_t)(&var);		info.type="FILE";info.type_size=sizeof(FILE);__IFI(1);InfoHashPut(&info);strcat(fields,"fp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field fp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.is_open";info.offset=(caddr_t)(&(var.is_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"is_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field is_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.initialize";info.offset=(caddr_t)(&(var.initialize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"initialize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field initialize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.leave_open";info.offset=(caddr_t)(&(var.leave_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"leave_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field leave_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.append";info.offset=(caddr_t)(&(var.append))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"append");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field append\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.flush";info.offset=(caddr_t)(&(var.flush))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flush");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field flush\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="xviewfile_type.xmax";info.offset=(caddr_t)(&(var.xmax))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"xmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object xviewfile_type, field xmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("xviewfile_type",fields);
}
void INFO_ascfile_type(){
struct ascfile_type var;Info info;char fields[2500];fields[0]='\0';info.name="ascfile_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="ascfile_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.fp";info.offset=(caddr_t)(&(var.fp))-(caddr_t)(&var);		info.type="FILE";info.type_size=sizeof(FILE);__IFI(1);InfoHashPut(&info);strcat(fields,"fp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field fp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.is_open";info.offset=(caddr_t)(&(var.is_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"is_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field is_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.initialize";info.offset=(caddr_t)(&(var.initialize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"initialize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field initialize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.leave_open";info.offset=(caddr_t)(&(var.leave_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"leave_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field leave_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.append";info.offset=(caddr_t)(&(var.append))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"append");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field append\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.flush";info.offset=(caddr_t)(&(var.flush))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flush");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field flush\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.float_format";info.offset=(caddr_t)(&(var.float_format))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"float_format");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field float_format\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="ascfile_type.notime";info.offset=(caddr_t)(&(var.notime))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"notime");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object ascfile_type, field notime\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("ascfile_type",fields);
}
void INFO_res_ascfile_type(){
struct res_ascfile_type var;Info info;char fields[2500];fields[0]='\0';info.name="res_ascfile_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="res_ascfile_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.fp";info.offset=(caddr_t)(&(var.fp))-(caddr_t)(&var);		info.type="FILE";info.type_size=sizeof(FILE);__IFI(1);InfoHashPut(&info);strcat(fields,"fp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field fp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.is_open";info.offset=(caddr_t)(&(var.is_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"is_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field is_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.initialize";info.offset=(caddr_t)(&(var.initialize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"initialize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field initialize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.leave_open";info.offset=(caddr_t)(&(var.leave_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"leave_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field leave_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.append";info.offset=(caddr_t)(&(var.append))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"append");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field append\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.flush";info.offset=(caddr_t)(&(var.flush))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flush");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field flush\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.float_format";info.offset=(caddr_t)(&(var.float_format))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"float_format");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field float_format\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.time_res";info.offset=(caddr_t)(&(var.time_res))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"time_res");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field time_res\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.value_res";info.offset=(caddr_t)(&(var.value_res))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"value_res");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field value_res\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.last_time";info.offset=(caddr_t)(&(var.last_time))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);InfoHashPut(&info);strcat(fields,"last_time");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field last_time\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.nvalues";info.offset=(caddr_t)(&(var.nvalues))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"nvalues");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field nvalues\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="res_ascfile_type.last_values";info.offset=(caddr_t)(&(var.last_values))-(caddr_t)(&var);		info.type="double";info.type_size=sizeof(double);__IFI(1);InfoHashPut(&info);strcat(fields,"last_values");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object res_ascfile_type, field last_values\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("res_ascfile_type",fields);
}
void INFO_spikehistory_type(){
struct spikehistory_type var;Info info;char fields[2500];fields[0]='\0';info.name="spikehistory_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="spikehistory_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.filename";info.offset=(caddr_t)(&(var.filename))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"filename");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field filename\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.fp";info.offset=(caddr_t)(&(var.fp))-(caddr_t)(&var);		info.type="FILE";info.type_size=sizeof(FILE);__IFI(1);InfoHashPut(&info);strcat(fields,"fp");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field fp\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.is_open";info.offset=(caddr_t)(&(var.is_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"is_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field is_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.initialize";info.offset=(caddr_t)(&(var.initialize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"initialize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field initialize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.leave_open";info.offset=(caddr_t)(&(var.leave_open))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"leave_open");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field leave_open\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.append";info.offset=(caddr_t)(&(var.append))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"append");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field append\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.flush";info.offset=(caddr_t)(&(var.flush))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flush");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field flush\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.float_format";info.offset=(caddr_t)(&(var.float_format))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"float_format");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field float_format\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="spikehistory_type.ident_toggle";info.offset=(caddr_t)(&(var.ident_toggle))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"ident_toggle");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object spikehistory_type, field ident_toggle\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("spikehistory_type",fields);
}
void INFO_oldgraph_type(){
struct oldgraph_type var;Info info;char fields[2500];fields[0]='\0';info.name="oldgraph_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="oldgraph_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.overlay";info.offset=(caddr_t)(&(var.overlay))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"overlay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field overlay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.xoffset";info.offset=(caddr_t)(&(var.xoffset))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"xoffset");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field xoffset\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.yoffset";info.offset=(caddr_t)(&(var.yoffset))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"yoffset");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field yoffset\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.last_plot";info.offset=(caddr_t)(&(var.last_plot))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"last_plot");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field last_plot\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldgraph_type.phase_plot";info.offset=(caddr_t)(&(var.phase_plot))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"phase_plot");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldgraph_type, field phase_plot\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("oldgraph_type",fields);
}
void INFO_oldxview_type(){
struct oldxview_type var;Info info;char fields[2500];fields[0]='\0';info.name="oldxview_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="oldxview_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.datatype";info.offset=(caddr_t)(&(var.datatype))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datatype");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field datatype\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.datasize";info.offset=(caddr_t)(&(var.datasize))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"datasize");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field datasize\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.mixed_data";info.offset=(caddr_t)(&(var.mixed_data))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"mixed_data");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field mixed_data\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.data";info.offset=(caddr_t)(&(var.data))-(caddr_t)(&var);		info.type="output_data_type";info.type_size=sizeof(struct output_data_type);__IFI(1);InfoHashPut(&info);strcat(fields,"data");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field data\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.ndata";info.offset=(caddr_t)(&(var.ndata))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"ndata");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field ndata\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.plotnum";info.offset=(caddr_t)(&(var.plotnum))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"plotnum");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field plotnum\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.display_mode";info.offset=(caddr_t)(&(var.display_mode))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"display_mode");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field display_mode\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="oldxview_type.color";info.offset=(caddr_t)(&(var.color))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"color");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object oldxview_type, field color\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("oldxview_type",fields);
}
void INFO_script_output_type(){
struct script_output_type var;Info info;char fields[2500];fields[0]='\0';info.name="script_output_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="script_output_type.name";info.offset=(caddr_t)(&(var.name))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"name");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field name\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.index";info.offset=(caddr_t)(&(var.index))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"index");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field index\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.object";info.offset=(caddr_t)(&(var.object))-(caddr_t)(&var);		info.type="object_type";info.type_size=sizeof(struct object_type);__IFI(1);InfoHashPut(&info);strcat(fields,"object");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field object\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.flags";info.offset=(caddr_t)(&(var.flags))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"flags");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field flags\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.nextfields";info.offset=(caddr_t)(&(var.nextfields))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"nextfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field nextfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.extfields";info.offset=(caddr_t)(&(var.extfields))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"extfields");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field extfields\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.x";info.offset=(caddr_t)(&(var.x))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"x");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field x\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.y";info.offset=(caddr_t)(&(var.y))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"y");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field y\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.z";info.offset=(caddr_t)(&(var.z))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"z");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field z\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.nmsgin";info.offset=(caddr_t)(&(var.nmsgin))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field nmsgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.msgin";info.offset=(caddr_t)(&(var.msgin))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgin");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field msgin\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.msgintail";info.offset=(caddr_t)(&(var.msgintail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgintail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field msgintail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.nmsgout";info.offset=(caddr_t)(&(var.nmsgout))-(caddr_t)(&var);		info.type="unsigned int";info.type_size=sizeof(unsigned int);InfoHashPut(&info);strcat(fields,"nmsgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field nmsgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.msgout";info.offset=(caddr_t)(&(var.msgout))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgout");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field msgout\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.msgouttail";info.offset=(caddr_t)(&(var.msgouttail))-(caddr_t)(&var);		info.type="Msg";info.type_size=sizeof(Msg);__IFI(1);InfoHashPut(&info);strcat(fields,"msgouttail");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field msgouttail\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.compositeobject";info.offset=(caddr_t)(&(var.compositeobject))-(caddr_t)(&var);		info.type="GenesisObject";info.type_size=sizeof(GenesisObject);__IFI(1);InfoHashPut(&info);strcat(fields,"compositeobject");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field compositeobject\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.componentof";info.offset=(caddr_t)(&(var.componentof))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"componentof");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field componentof\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.parent";info.offset=(caddr_t)(&(var.parent))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"parent");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field parent\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.child";info.offset=(caddr_t)(&(var.child))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"child");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field child\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Element";info.type_size=sizeof(Element);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.command";info.offset=(caddr_t)(&(var.command))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(1);InfoHashPut(&info);strcat(fields,"command");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field command\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.argc";info.offset=(caddr_t)(&(var.argc))-(caddr_t)(&var);		info.type="int";info.type_size=sizeof(int);InfoHashPut(&info);strcat(fields,"argc");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field argc\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="script_output_type.argv";info.offset=(caddr_t)(&(var.argv))-(caddr_t)(&var);		info.type="char";info.type_size=sizeof(char);__IFI(2);InfoHashPut(&info);strcat(fields,"argv");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object script_output_type, field argv\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("script_output_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_output(){
INFO_output_data_type();
INFO_output_type();
INFO_file_type();
INFO_xviewfile_type();
INFO_ascfile_type();
INFO_res_ascfile_type();
INFO_spikehistory_type();
INFO_oldgraph_type();
INFO_oldxview_type();
INFO_script_output_type();
}
