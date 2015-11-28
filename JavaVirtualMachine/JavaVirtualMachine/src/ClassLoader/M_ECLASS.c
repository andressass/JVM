//#################################################################################################
/*! \file M_ECLASS.c
 *
 *  \brief Modulo Exibidor de arquivos ".class".
 *
 *  Modulo responsavel por implementar os metodos relacionados a exibicao de um arquivo ".class".
 */
//##################################################################################################


#define ECLASS_SERV


#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/Estruturas/OPCODES.h"
#include <string.h>
#include <wchar.h>

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um double em big-endian order.
 *
 * \param high_bytes    Bytes de mais alta ordem.
 * \param low_bytes     Bytes de mais baixa ordem.
 */
double u4ToDouble(u4 high_bytes, u4 low_bytes){
    double resultado;
    unsigned char b[8]; //vetor de 8 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = low_bytes >> i * 8;
    for (int i = 4; i < 8; i++) b[i] = high_bytes >> i * 8;
    
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um float em big-endian order.
 *
 * \param bytes    Bytes em u4.
 */
float u4ToFLoat(u4 bytes){
    
    float resultado;
    unsigned char b[4]; //vetor de 4 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = bytes >> i * 8;
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
wchar_t * getUnicodeFromConstantPool(cp_info* cp, u2 index){
    
    int i;
    wchar_t* string = (wchar_t * ) malloc( (cp[index-1].u.Utf8.lenght+1) * sizeof(wchar_t));
    
    for (i = 0; i < cp[index-1].u.Utf8.lenght; i++) string[i] = cp[index-1].u.Utf8.bytes[i];
    
    string[i] = '\0'; //Ultimo caractere
    
    return string;
}


//--------------------------------------------------------------------------------------------------
char * getUTF8FromConstantPool(cp_info* cp, u2 index){
    
    wchar_t *unicode = getUnicodeFromConstantPool(cp, index);
    char * result = (char*) malloc(wcslen(unicode) * sizeof(char));
    
    wcstombs(result, unicode, wcslen(unicode)+1);
    
    free(unicode);
    
    return result;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao dos campos nome e descritor de uma estrutura NameAndType do 
 * pool de constantes
 *
 * \param cp    ponteiro para o pool de constantes
 * \param tag   tag do NameAndType no pool de constantes.
 */
void printNameAndTypeInfoFromConstantPool(cp_info* cp, u2 index ){
    printf(" (Name: \"%ls\"", getUnicodeFromConstantPool(cp, cp[index-1].u.NameAndType.name_index));
    printf(" Descr: \"%ls\")", getUnicodeFromConstantPool(cp, cp[index-1].u.NameAndType.descriptor_index));
}


//--------------------------------------------------------------------------------------------------
char* getClassNameFromConstantPool(cp_info* cp, u2 index){
    
    return  getUTF8FromConstantPool(cp, cp[index-1].u.Class.name_index);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dado uma referencia para uma lista de tabela de excecoes e seu respectivo tamanho, 
 * cria, preenche e retorna uma referencia para um vetor de estruturas exception table.
 *
 * \param code Ponteiro para o vetor que contem as excetion_tables
 * \param exception_table_length Numero de elementos na tabela de excessoes
 * \param cp ponteiro para o pool de constantes
 * \return Ponteiro para um vetor de tabela de excessoes preenchida
 */
ExceptionTable* parseExceptionTables(u1* exceptionTableList, u2 exception_table_length){
    
    u1* c = exceptionTableList;
    ExceptionTable* exceptionTable = (ExceptionTable*)
                                    malloc(exception_table_length * sizeof(ExceptionTable));
    
    for ( int i = 0; i < exception_table_length; i++) {
        
        exceptionTable[i].start_pc = *c++;
        exceptionTable[i].start_pc = exceptionTable[i].start_pc << 8 | *c++;
        
        exceptionTable[i].end_pc = *c++;
        exceptionTable[i].end_pc = exceptionTable[i].end_pc << 8 | *c++;
        
        exceptionTable[i].handler_pc = *c++;
        exceptionTable[i].handler_pc = exceptionTable[i].handler_pc << 8 | *c++;
        
        exceptionTable[i].catch_type = *c++;
        exceptionTable[i].catch_type = exceptionTable[i].catch_type << 8 | *c++;
        
    }
    
    return exceptionTable;
}


//--------------------------------------------------------------------------------------------------
CodeAttribute* parseCode(u1* info){
    CodeAttribute* code = (CodeAttribute*) malloc(sizeof(CodeAttribute));
    
    int index = 0;
    
    code->max_stack = info[index++];
    code->max_stack = code->max_stack << 8 | info[index++];
    
    code->max_locals = info[index++];
    code->max_locals = code->max_locals << 8 | info[index++];
    
    code->code_length = info[index++];
    code->code_length = code->code_length << 8 | info[index++];
    code->code_length = code->code_length << 8 | info[index++];
    code->code_length = code->code_length << 8 | info[index++];
    
    
    code->code = &info[index];
    
    index += code->code_length;
    
    code->exception_table_length = info[index++];
    code->exception_table_length = code->exception_table_length << 8 | info[index++];
    
    code->exception_table = parseExceptionTables(&info[index], code->exception_table_length);
    
    index += code->exception_table_length * 4 * sizeof(u2); //Tamanho da Tabela de excessao = 4*u2
    
    code->attributes_count = info[index++];
    code->attributes_count = code->attributes_count << 8 | info[index++];
    code->attributes = &info[index];
    
    return code;
}

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao de um campo do pool de constantes
 *
 * \param cp               estrutura de pool de constante a ser exibida
 * \param constant_pool    ponteiro para o pool de constantes da classe
 */
void printFromPool(cp_info* cp, cp_info* constant_pool){
    
    switch (cp->tag) {
            
        case CONSTANT_Class:
            printf("CONSTANT_Class_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 name_index: %d", cp->u.Class.name_index);
            printf(" (\"%ls\")", getUnicodeFromConstantPool(constant_pool, cp->u.Class.name_index));
            printf("\n}\n");
            break;
            
        case CONSTANT_Fieldref:
            printf("CONSTANT_Fieldref_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 class_index: %d", cp->u.Fieldref.class_index);
            
            //Imprimimos o nome da classe indicada por class_index
            printf(" (\"%s\")", getClassNameFromConstantPool(constant_pool,
                                                         cp->u.Fieldref.class_index));
            
            printf("\n\tu2 name_and_type_index: %d", cp->u.Fieldref.name_and_type_index);
            
            //Imprimimos os atributos de name and type do indice name_and_type_index
            printNameAndTypeInfoFromConstantPool(constant_pool,
                                                 cp->u.Fieldref.name_and_type_index);
            printf("\n}\n");
            break;
            
        case CONSTANT_NameAndType:
            printf("CONSTANT_NameAndType_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 name_index: %d", cp->u.NameAndType.name_index);
            printf(" (\"%ls\")", getUnicodeFromConstantPool(constant_pool,
                                                         cp->u.NameAndType.name_index));
            printf("\n\tu2 descriptor_index: %d", cp->u.NameAndType.descriptor_index);
            printf(" (\"%ls\")", getUnicodeFromConstantPool(constant_pool,
                                                         cp->u.NameAndType.descriptor_index));
            printf("\n}\n");
            break;
            
        case CONSTANT_Utf8:
            printf("CONSTANT_Utf8_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 lenght: %d", cp->u.Utf8.lenght);
            printf("\n\tu1 bytes[%d]: ", cp->u.Utf8.lenght);
            printf("\"%ls\"", getUnicodeFromConstantPool(cp,1));
            printf("\n}\n");
            break;
            
        case CONSTANT_Methodref:
            printf("CONSTANT_Methodref_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 class_index: %d", cp->u.Methodref.class_index);
            
            //Imprimimos o nome da classe indicada por class_index
            printf(" (\"%s\")", getClassNameFromConstantPool(constant_pool,
                                                             cp->u.Methodref.class_index));
            
            printf("\n\tu2 name_and_type_index: %d", cp->u.Methodref.name_and_type_index);
            
            //Imprimimos os atributos de name and type indice name_and_type_index
            printNameAndTypeInfoFromConstantPool(constant_pool,
                                                 cp->u.Methodref.name_and_type_index);
            printf("\n}\n");
            break;
            
        case CONSTANT_InterfaceMethodref:
            printf("CONSTANT_InterfaceMethodref_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 class_index: %d", cp->u.InterfaceMethodref.class_index);
            
            //Imprimimos o nome da classe indicada por class_index
            printf(" (\"%s\")", getClassNameFromConstantPool(constant_pool,
                                                             cp->u.InterfaceMethodref.class_index));
            
            printf("\n\tu2 name_and_type_index: %d", cp->u.InterfaceMethodref.name_and_type_index);
            
            //Imprimimos os atributos de name and type indice name_and_type_index
            printNameAndTypeInfoFromConstantPool(constant_pool,
                                                 cp->u.InterfaceMethodref.name_and_type_index);
            printf("\n}\n");
            break;
            
        case CONSTANT_String:
            printf("CONSTANT_String_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu2 string_index: %d", cp->u.String.string_index);
            printf(" (\"%ls\")", getUnicodeFromConstantPool(constant_pool,
                                                         cp->u.String.string_index));
            printf("\n}\n");
            break;
            
        case CONSTANT_Integer:
            printf("CONSTANT_Integer_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu4 bytes: %d", cp->u.Integer.bytes);
            printf("\n}\n");
            break;
            
        case CONSTANT_Float:
            printf("CONSTANT_Float_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu4 bytes: %f", u4ToFLoat(cp->u.Float.bytes));
            printf("\n}\n");
            break;
            
        case CONSTANT_Long:
            printf("CONSTANT_Long_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            
            //Unimos os dois u4 em um long long (u8)
            long long bytesl = cp->u.Long.high_bytes;
            bytesl = bytesl << 32 | cp->u.Long.low_bytes;
            
            printf("\n\tu4 high_bytes: 0x%x", cp->u.Long.high_bytes);
            printf("\n\tu4 low_bytes: 0x%x", cp->u.Long.low_bytes);
            printf("\n\t(u8 bytes: %lld)", bytesl);
            printf("\n}\n");
            cp++; // Ocupa 2 indices
            break;
            
        case CONSTANT_Double:
            printf("CONSTANT_Double_info {");
            printf("\n\tu1 tag: %d", cp->tag);
            printf("\n\tu4 high_bytes: 0x%x", cp->u.Double.high_bytes);
            printf("\n\tu4 low_bytes: 0x%x", cp->u.Double.low_bytes);
            printf("\n\t(u8 bytes: %lf)", u4ToDouble(cp->u.Double.high_bytes, cp->u.Double.low_bytes));
            printf("\n}\n");
            cp++; // Ocupa 2 indices
            break;
            
        default:
            break;
    }
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao do pool de constantes de uma estrutura ArqClass
 *
 * \param arq_class Estrutura ArqClass contendo o ponteiro para o pool de constantes a ser exibido
 */
void exibeCtePool(ArqClass* arq_class){

    cp_info* cp;
    //Para cada elemento do pool de constantes
    for (cp = arq_class->constant_pool;
         cp < arq_class->constant_pool + arq_class->constant_pool_count - 1;
         cp++)
    {
        printf("%ld. ", (cp - arq_class->constant_pool +1));
        //Imprimimos o elemento
        printFromPool(cp, arq_class->constant_pool);
    }
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao das flags de acesso setadas em um u2
 *
 * \param access_flags  u2 contendo as flags de acesso
 * \param is_class      int simulando booleano que verifica se a flag eh ou nao de classe
 */
void exibeAccessFlags(u2 access_flags, int is_class){
    
    if (access_flags & ACC_PUBLIC)      printf("public ");
    if (access_flags & ACC_PRIVATE)     printf("private ");
    if (access_flags & ACC_PROTECTED)   printf("protected ");
    if (access_flags & ACC_STATIC)      printf("static ");
    if (access_flags & ACC_FINAL)       printf("final ");
    if (is_class) {
        if (access_flags & ACC_SUPER)       printf("super ");
    }
    else{
        if (access_flags & ACC_SYNCHRONIZED) printf("synchronized ");
    }
    if (access_flags & ACC_VOLATILE)    printf("volatile ");
    if (access_flags & ACC_TRANSIENT)   printf("transient ");
    if (access_flags & ACC_NATIVE)      printf("native ");
    if (access_flags & ACC_INTERFACE)   printf("interface ");
    if (access_flags & ACC_ABSTRACT)    printf("abstract ");
    if (access_flags & ACC_STRICT)      printf("strict ");
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao das interfaces de uma estrutura ArqClass
 *
 * \param arq_class Estrutura ArqClass contendo o ponteiro as interfaces
 */
void exibeInterfaces(ArqClass* arq_class){
    
    for (int i = 0; i < arq_class->interfaces_count; i++) {
        printf("\n %d (\"%ls\")", arq_class->interfaces[i],
        getUnicodeFromConstantPool(arq_class->constant_pool,
                                arq_class->constant_pool[arq_class->interfaces[i]-1].u.Class.name_index));
    }
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao de um bytecode
 *
 * \param bytecode Bytecode a ser exibido.
 */
void printByteCode(u1* bytecode){
    
    u1 mnemonic = bytecode[0];
    
    printf("\n\t\t\t%s", getOpcodeName(mnemonic));
    bytecode++;
    
    //TODO opcode com numero de atributos variavel (-1)
    for (int i = 0; i < getOpcodeAttributesNumber(mnemonic) ; i++) {
        printf(" 0x%.2x", bytecode[i]);
        bytecode++;
    }
    
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao de um vetor de bytecodes
 *
 * \param bytecodes Vetor de bytecodes
 * \param code_lenght tamanho do vetor de bytecodes
 */
void printByteCodes(u1* bytecodes, u4 code_length){
    
    u1* bc = bytecodes;
    printf("\n\t\t{ ");

    for ( bc = bytecodes; bc < bytecodes + code_length; bc++) {
        printByteCode(bc);
    }
    printf("\n\t\t}");
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao de um atributo
 *
 * \param attribute ponteiro para o atributo a ser exibido
 * \param cp    ponteiro para o pool de constantes
 */
void exibeAtributo(attribute_info* attribute, cp_info* cp); //A ser implementada abaixo...


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao dos atributos de um Atributo CODE
 *
 * \param code Ponteiro para o vetor de atributos de code
 * \param attributes_count Numero de atributos
 * \param cp ponteiro para o pool de constantes
 */
void printCodeAttributes(u1* code, u4 attributes_count, cp_info* cp){
    
    u1* c = code;
    
    printf("\n\t\t{");
    
    for ( int i = 0; i < attributes_count; i++) {
        attribute_info* attr = (attribute_info*) malloc(sizeof(attribute_info));
        
        attr->attribute_name_index = *c++;
        attr->attribute_name_index = attr->attribute_name_index << 8 | *c++;

        attr->attribute_length = *c++;
        attr->attribute_length = attr->attribute_length << 8 | *c++;
        attr->attribute_length = attr->attribute_length << 8 | *c++;
        attr->attribute_length = attr->attribute_length << 8 | *c++;
        
        attr->info = (u1*) malloc(attr->attribute_length * sizeof(u1*));
        
        for (int j = 0; j < attr->attribute_length; j++) attr->info[j] = *c++;
        
        exibeAtributo(attr, cp);
        
        free(attr->info);
        free(attr);
    }
    printf("\n\t\t}");
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao das tabelas de excessoes de um Atributo CODE
 *
 * \param code Ponteiro para uma lista de exceptionTables
 * \param exception_table_length Numero de elementos na tabela de excessoes
 * \param cp ponteiro para o pool de constantes
 */
void printCodeExceptions(ExceptionTable* excTable, u2 exception_table_length, cp_info* cp){
    
    printf("\n\t\t{");
    
    for ( int i = 0; i < exception_table_length; i++) {
        printf("\n\t\t\t{");
        printf("\n\t\t\tSTART_PC: %d", excTable[i].start_pc);
        printf("\n\t\t\tEND_PC: %d", excTable[i].end_pc);
        printf("\n\t\t\tHANDLER_PC: %d", excTable[i].handler_pc);
        printf("\n\t\t\tCATCH_TYPE: %d", excTable[i].catch_type);
        
        printf("\n(((((((((((((((\n");
        printFromPool(&cp[excTable[i].catch_type], cp);
        printf(")))))))))))))))\n");
        printf("\n\t\t\t}");
    }
    printf("\n\t\t}");
}


//--------------------------------------------------------------------------------------------------
//
void exibeAtributo(attribute_info* attribute, cp_info* cp){
    
    //Exibimos o nome
    printf("\n\t\tNAME_INDEX:\t\t %d ", attribute->attribute_name_index);
    printf("(\"%ls\")", getUnicodeFromConstantPool(cp, attribute->attribute_name_index));
    
    //tamanho em bytes do restande do atributo
    printf("\n\t\tATTRIBUTES_LENGHT:\t %d ", attribute->attribute_length);
    
    //Verificamos qual o tipo de atributo
    
    //Caso seja ConstantValue
    if (wcscmp(getUnicodeFromConstantPool(cp, attribute->attribute_name_index), ATT_ConstantValue)==0) {
        u2 constantvalue_index = attribute->info[0];
        constantvalue_index = constantvalue_index << 8 | attribute->info[1];
        printf("\n\t\tCONSTANT_VALUE INDEX:\t\t %d ", constantvalue_index);
        printf("\n(((((((((((((((\n");
        printFromPool(&cp[constantvalue_index-1], cp);
        printf(")))))))))))))))\n");
        
    }
    //Caso seja CODE
    else if (wcscmp(getUnicodeFromConstantPool(cp, attribute->attribute_name_index), ATT_Code)==0) {
        
        CodeAttribute* code = parseCode(attribute->info);
        
        printf("\n\t\tMAX_STACK:\t\t %d ", code->max_stack);
        
        printf("\n\t\tMAX_LOCALS:\t\t %d ", code->max_locals);
        
        printf("\n\t\tCODE_LENGHT:\t\t %d ", code->code_length);
     
        printByteCodes(code->code, code->code_length);
        
        printf("\n\t\tEXCEPTION_TABLE_LENGHT:\t %d ", code->exception_table_length);
        printCodeExceptions(code->exception_table, code->exception_table_length, cp);
        
        printf("\n\t\tATTRIBUTES_COUNT:\t %d ", code->attributes_count);
        printCodeAttributes(code->attributes, code->attributes_count, cp);
    }
    //Caso seja Exception
    else if (wcscmp(getUnicodeFromConstantPool(cp, attribute->attribute_name_index), ATT_Exceptions)==0) {
        
        int index = 0;
        
        u2 number_of_exceptions = attribute->info[index++];
        number_of_exceptions = number_of_exceptions << 8 | attribute->info[index++];
        printf("\n\t\tNUMBER_OF_EXECPTIONS:\t\t %d ", number_of_exceptions);
        
        for (int i = 0; i < number_of_exceptions; i ++) {
            printf("\n%d. (\n", i);
            printFromPool(&cp[attribute->info[index++]-1], cp);
            printf(")\n");
        }
    }
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao dos atributos de uma estrutura arqClass
 *
 * \param arqClass ponteiro a estrutura com os atributos a serem exibidos
 */
void exibeAtributos(ArqClass* arq_class){
    
    for (int i = 0; i < arq_class->attributes_count; i++) {
        printf("\n%d.{", i+1);
        exibeAtributo(arq_class->attributes[i], arq_class->constant_pool);
        printf("\n}");
    }
    
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao de campos ou metodos
 *
 * \param fm    ponteiro para o campo ou metodo a ser exibido
 * \param count quantidade de campos ou metodos a serem exibidos
 * \param cp    ponteiro para o pool de constantes
 */
void exibeCampMetd(field_or_method* fm, u2 count, cp_info* cp){

    for (int i = 0; i < count; i++) {
        
        printf("\n%d.{", i+1);
        //Exibimos as flags de acesso
        printf("\n\tACCESS_FLAGS:\t\t %d ", fm->access_flags);
        printf("( ");
        exibeAccessFlags(fm[i].access_flags, 0);
        printf(")");
        
        //Exibimos o nome
        printf("\n\tNAME_INDEX:\t\t %d ", fm[i].name_index);
        printf("(\"%ls\")", getUnicodeFromConstantPool(cp,
                                                    fm[i].name_index));
        
        //Exibimos o descritor
        printf("\n\tDESCRIPTOR_INDEX:\t %d ", fm[i].descriptor_index);
        printf("(\"%ls\")", getUnicodeFromConstantPool(cp,
                                                    fm[i].descriptor_index));
        
        //Exibimos os atributos
        printf("\n\tATTRIBUTES_COUNT:\t %d ", fm[i].attributes_count);
        for (int j= 0; j< fm[i].attributes_count; j++) {
            printf("\n\t%d.{", j+1);
            exibeAtributo(fm[i].attributes[j], cp);
            printf("\n\t}");
        }
        
        printf("\n  }");
        
    }

}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao dos campos de uma estrutura arqClass
 *
 * \param arq_class Estrutura ArqClass
 */
void exibeCampos(ArqClass* arq_class){
    exibeCampMetd(arq_class->fields, arq_class->fields_count, arq_class->constant_pool);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao dos metodos de uma estrutura arqClass
 *
 * \param arq_class Estrutura ArqClass
 */
void exibeMetodos(ArqClass* arq_class){
    exibeCampMetd(arq_class->methods, arq_class->methods_count, arq_class->constant_pool);
}


//--------------------------------------------------------------------------------------------------
resultado LECLASS_exibidor(ArqClass* arq_class){
    
    printf("\n####################################################\n");
    printf("DETALHES DO ARQUIVO .CLASS");
    printf("\n####################################################\n");
    printf("MAGIC:\t\t\t 0x%x", arq_class->magic);
    printf("\nMINOR_VERSION:\t\t %d", arq_class->minor_version);
    printf("\nMAJOR_VERSION:\t\t %d", arq_class->major_version);
    printf("\nCONSTANT_POOL_COUNT:\t %d", arq_class->constant_pool_count);
    printf("\n----------------------------------------------------\n");
    printf("CONSTANT POOL:");
    printf("\n----------------------------------------------------\n");
    exibeCtePool(arq_class);
    printf("\n----------------------------------------------------\n");
    printf("ACCESS_FLAGS:\t %d ", arq_class->access_flags);
    printf("( ");
    exibeAccessFlags(arq_class->access_flags, 1);
    printf(")");
    
    printf("\nTHIS_CLASS:\t %d ", arq_class->this_class);
    printf("(\"%ls\")",
           getUnicodeFromConstantPool(arq_class->constant_pool,
                                   arq_class->constant_pool[arq_class->this_class-1].u.Class.name_index));
    printf("\nSUPER_CLASS:\t %d ", arq_class->super_class);
    printf("(\"%ls\")",
           getUnicodeFromConstantPool(arq_class->constant_pool,
                                   arq_class->constant_pool[arq_class->super_class-1].u.Class.name_index));
    
    printf("\nINTERFACES_COUNT: %d", arq_class->interfaces_count);
    printf("\n----------------------------------------------------\n");
    printf("INTERFACES: ");
    exibeInterfaces(arq_class);
    printf("\n----------------------------------------------------\n");
    
    printf("FIELDS_COUNT:\t %d", arq_class->fields_count);
    printf("\n----------------------------------------------------\n");
    printf("FIELDS: ");
    exibeCampos(arq_class);
    printf("\n----------------------------------------------------\n");
    
    printf("METHODS_COUNT:\t %d", arq_class->methods_count);
    printf("\n----------------------------------------------------\n");
    printf("METHODS: ");
    exibeMetodos(arq_class);
    printf("\n----------------------------------------------------\n");
    
    printf("ATTRIBUTES_COUNT:\t %d", arq_class->attributes_count);
    printf("\n----------------------------------------------------\n");
    printf("ATTRIBUTES: ");
    exibeAtributos(arq_class);
    printf("\n----------------------------------------------------\n");
    printf("\n####################################################\n");
    
    return LinkageSuccess;

}


//--------------------------------------------------------------------------------------------------
void LECLASS_exibeErroOperacao(resultado resultado, const char* fileName){
    
    switch (resultado) {
        case LinkageError_NoClassDefFoundError:
            printf("\nErro de abertura do arquivo \"%s\".\n", fileName);
            break;
            
        case LinkageError_ClassFormatError:
            printf("\nArquivo .class invalido. Arquivo:\"%s\".\n", fileName);
            break;
            
        case LinkageError_UnsupportedClassVersionError:
            printf("\nA versao do arquivo .class eh imcompativel. Arquivo: \"%s\".\n", fileName);
            break;
            
        default:
            break;
    }

}



