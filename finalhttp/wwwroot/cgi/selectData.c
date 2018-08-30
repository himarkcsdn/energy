#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

void select_data()
{
	MYSQL *mysql_fd = mysql_init(NULL);
	if(mysql_real_connect(mysql_fd, "127.0.0.1", "root",\
				"", "submit", 3306, NULL, 0) == NULL){
		printf("connect failed!\n");
		return;
	}
	printf("connect mysql success!\n");

	char sql[1024];

	sprintf(sql, "SELECT * FROM login");
	mysql_query(mysql_fd, sql);

	MYSQL_RES *res = mysql_store_result(mysql_fd);
	int row = mysql_num_rows(res);
	int col = mysql_num_fields(res);
	MYSQL_FIELD *field = mysql_fetch_fields(res);
	int i = 0;
	for(; i < col; i++){
		printf("%s\t", field[i].name);
	}
	printf("\n");

	printf("<table border=\"1\">");
	for(i=0; i < row; i++){
		MYSQL_ROW rowData = mysql_fetch_row(res);
		int j = 0;
		printf("<tr>");
		for(; j < col; j++){
			printf("<td>%s</td>", rowData[j]);
		}
		printf("</tr>");
	}
	printf("</table>");

	mysql_close(mysql_fd);
}

int main()
{
	char data[1024];
	if(getenv("METHOD")){
		if(strcasecmp("GET", getenv("METHOD")) == 0){
			strcpy(data, getenv("QUERY_STRING"));
		}else{
			int content_length = atoi(getenv("CONTENT_LENGTH"));
			int i = 0;
			for(; i < content_length; i++){
				read(0, data+i, 1);
			}
			data[i] = 0;
		}
	}

	select_data();
	return 0;
}






















