#include"global.h"

void executeCommand(){

    switch(parsedQuery.queryType){
        case CLEAR: executeCLEAR(); break;
        case CROSS: executeCROSS(); break;
        case DISTINCT: executeDISTINCT(); break;
        case EXPORT: executeEXPORT(); break;
        case EXPORTMATRIX: executeEXPORTMATRIX(); break;
        case INDEX: executeINDEX(); break;
        case JOIN: executeJOIN(); break;
        case LIST: executeLIST(); break;
        case LOAD: executeLOAD(); break;
        case LOADMATRIX: executeLOADMATRIX(); break;
        case PRINT: executePRINT(); break;
        case PRINTMATRIX: executePRINTMATRIX(); break;
        case CHECKSYMMETRY: executeCHECKSYMMETRY(); break;
        case RENAMEMATRIX: executeRENAMEMATRIX(); break;
        case COMPUTE: executeCOMPUTE(); break;
        case TRANSPOSE: executeTRANSPOSEMATRIX(); break;
        case PROJECTION: executePROJECTION(); break;
        case RENAME: executeRENAME(); break;
        case SELECTION: executeSELECTION(); break;
        case SORT: executeSORT(); break;
        case ORDER: executeORDER(); break;
        case GROUP: executeGROUP(); break;
        case SOURCE: executeSOURCE(); break;
        default: cout<<"PARSING ERROR"<<endl;
    }

    return;
}

void printRowCount(int rowCount){
    cout<<"\n\nRow Count: "<<rowCount<<endl;
    return;
}