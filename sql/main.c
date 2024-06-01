#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include <sql.h>
#include <sqlext.h>

void printTable(char *r)
{
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    // Allocate an environment handle
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    // We want ODBC 3 support
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
    // Allocate a connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    // Connect to the DSN, MyDSN
    SQLDriverConnect(dbc, NULL, (SQLCHAR *)"DRIVER={MySQL ODBC 8.0 Driver};SERVER=localhost;DATABASE=test1;USER=root;PASSWORD=123456;", SQL_NTS,
                     outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_COMPLETE);

    // Allocate a statement handle
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    // Prepare our SQL query
    char query[256];
    sprintf(query, "SELECT * FROM %s", r);
    SQLExecDirect(stmt, (SQLCHAR *)query, SQL_NTS);

    // Get the number of columns
    SQLSMALLINT columns;
    SQLNumResultCols(stmt, &columns);

    // Fetch the header
    for (SQLSMALLINT i = 1; i <= columns; i++)
    {
        SQLCHAR columnName[128];
        SQLSMALLINT columnNameLen;
        SQLDescribeCol(stmt, i, columnName, sizeof(columnName), &columnNameLen, NULL, NULL, NULL, NULL);
        printf("%s\t", columnName);
    }
    printf("\n");

    // Fetch each row, and print its columns
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        for (SQLSMALLINT i = 1; i <= columns; i++)
        {
            SQLCHAR buf[512];
            SQLLEN indicator;
            SQLGetData(stmt, i, SQL_C_CHAR, buf, sizeof(buf), &indicator);
            // If the field is NULL, indicator will be SQL_NULL_DATA
            if (indicator == SQL_NULL_DATA)
                strcpy((char *)buf, "NULL");
            printf("%s\t", buf);
        }
        printf("\n");
    }

    // Clean up
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
}

int main()
{
    char *tableName = "books";
    printTable(tableName);
    return 0;
}