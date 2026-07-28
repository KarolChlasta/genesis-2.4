#include "syn_ext.h"

#define __BZ BZERO(&info,sizeof(Info))
#define __IFI(F) info.field_indirection = F
#define __IFT info.function_type = 1
#define __IND(N) info.dimensions = N
#define __IDS(S,N) info.dimension_size[S] = N
void INFO_connection_synapse_type(){
struct connection_synapse_type var;Info info;char fields[2500];fields[0]='\0';info.name="connection_synapse_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="connection_synapse_type.target";info.offset=(caddr_t)(&(var.target))-(caddr_t)(&var);		info.type="Segment";info.type_size=sizeof(Segment);__IFI(1);InfoHashPut(&info);strcat(fields,"target");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field target\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Connection";info.type_size=sizeof(Connection);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.weight";info.offset=(caddr_t)(&(var.weight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.delay";info.offset=(caddr_t)(&(var.delay))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"delay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field delay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.plastic_weight";info.offset=(caddr_t)(&(var.plastic_weight))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"plastic_weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field plastic_weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.base_weight";info.offset=(caddr_t)(&(var.base_weight))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"base_weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field base_weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.transient_weight";info.offset=(caddr_t)(&(var.transient_weight))-(caddr_t)(&var);		info.type="unsigned char";info.type_size=sizeof(unsigned char);InfoHashPut(&info);strcat(fields,"transient_weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field transient_weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.state_age";info.offset=(caddr_t)(&(var.state_age))-(caddr_t)(&var);		info.type="unsigned char";info.type_size=sizeof(unsigned char);InfoHashPut(&info);strcat(fields,"state_age");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field state_age\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="connection_synapse_type.activity_level";info.offset=(caddr_t)(&(var.activity_level))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"activity_level");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object connection_synapse_type, field activity_level\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("connection_synapse_type",fields);
}
void INFO_synapseA_type(){
struct synapseA_type var;Info info;char fields[2500];fields[0]='\0';info.name="synapseA_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="synapseA_type.target";info.offset=(caddr_t)(&(var.target))-(caddr_t)(&var);		info.type="Segment";info.type_size=sizeof(Segment);__IFI(1);InfoHashPut(&info);strcat(fields,"target");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field target\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseA_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Connection";info.type_size=sizeof(Connection);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseA_type.weight";info.offset=(caddr_t)(&(var.weight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseA_type.delay";info.offset=(caddr_t)(&(var.delay))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"delay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field delay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseA_type.time";info.offset=(caddr_t)(&(var.time))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"time");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field time\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseA_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseA_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("synapseA_type",fields);
}
void INFO_synapseB_type(){
struct synapseB_type var;Info info;char fields[2500];fields[0]='\0';info.name="synapseB_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="synapseB_type.target";info.offset=(caddr_t)(&(var.target))-(caddr_t)(&var);		info.type="Segment";info.type_size=sizeof(Segment);__IFI(1);InfoHashPut(&info);strcat(fields,"target");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field target\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Connection";info.type_size=sizeof(Connection);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.weight";info.offset=(caddr_t)(&(var.weight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.delay";info.offset=(caddr_t)(&(var.delay))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"delay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field delay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.time";info.offset=(caddr_t)(&(var.time))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"time");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field time\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.rate";info.offset=(caddr_t)(&(var.rate))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"rate");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field rate\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB_type.maxweight";info.offset=(caddr_t)(&(var.maxweight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"maxweight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB_type, field maxweight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("synapseB_type",fields);
}
void INFO_synapseB1_type(){
struct synapseB1_type var;Info info;char fields[2500];fields[0]='\0';info.name="synapseB1_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="synapseB1_type.target";info.offset=(caddr_t)(&(var.target))-(caddr_t)(&var);		info.type="Segment";info.type_size=sizeof(Segment);__IFI(1);InfoHashPut(&info);strcat(fields,"target");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field target\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Connection";info.type_size=sizeof(Connection);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.weight";info.offset=(caddr_t)(&(var.weight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.delay";info.offset=(caddr_t)(&(var.delay))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"delay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field delay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.rate";info.offset=(caddr_t)(&(var.rate))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"rate");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field rate\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseB1_type.maxweight";info.offset=(caddr_t)(&(var.maxweight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"maxweight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseB1_type, field maxweight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("synapseB1_type",fields);
}
void INFO_synapseC_type(){
struct synapseC_type var;Info info;char fields[2500];fields[0]='\0';info.name="synapseC_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="synapseC_type.target";info.offset=(caddr_t)(&(var.target))-(caddr_t)(&var);		info.type="Segment";info.type_size=sizeof(Segment);__IFI(1);InfoHashPut(&info);strcat(fields,"target");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field target\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.next";info.offset=(caddr_t)(&(var.next))-(caddr_t)(&var);		info.type="Connection";info.type_size=sizeof(Connection);__IFI(1);InfoHashPut(&info);strcat(fields,"next");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field next\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.weight";info.offset=(caddr_t)(&(var.weight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.delay";info.offset=(caddr_t)(&(var.delay))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"delay");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field delay\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.time";info.offset=(caddr_t)(&(var.time))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"time");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field time\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.state";info.offset=(caddr_t)(&(var.state))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"state");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field state\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.rate";info.offset=(caddr_t)(&(var.rate))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"rate");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field rate\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.scale";info.offset=(caddr_t)(&(var.scale))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"scale");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field scale\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.maxweight";info.offset=(caddr_t)(&(var.maxweight))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"maxweight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field maxweight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
__BZ;info.name="synapseC_type.orig_gmax";info.offset=(caddr_t)(&(var.orig_gmax))-(caddr_t)(&var);		info.type="float";info.type_size=sizeof(float);InfoHashPut(&info);strcat(fields,"orig_gmax");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object synapseC_type, field orig_gmax\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("synapseC_type",fields);
}
void INFO_rel_connection_synapse_type(){
struct rel_connection_synapse_type var;Info info;char fields[2500];fields[0]='\0';info.name="rel_connection_synapse_type";info.type_size=sizeof(var);InfoHashPut(&info);
__BZ;info.name="rel_connection_synapse_type.base_weight";info.offset=(caddr_t)(&(var.base_weight))-(caddr_t)(&var);		info.type="short";info.type_size=sizeof(short);InfoHashPut(&info);strcat(fields,"base_weight");strcat(fields,"\n");
if (strlen(fields) > 2500) { Error(); printf("Field size too long for object rel_connection_synapse_type, field base_weight\n**See sys/code_sym.c and increase the value of MAX_FIELDS_SIZE\n\n"); }
FieldHashPut("rel_connection_synapse_type",fields);
}
#undef __BZ
#undef __IFI
#undef __IFT
#undef __IND
#undef __IDS
void DATA_synapse(){
INFO_connection_synapse_type();
INFO_synapseA_type();
INFO_synapseB_type();
INFO_synapseB1_type();
INFO_synapseC_type();
INFO_rel_connection_synapse_type();
}
