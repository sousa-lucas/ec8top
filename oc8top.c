#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"
#include "versaoso.h"
#include "bateria.h"
#include "numprocessos.h"
#include "infomemoria.h"
#include "cpu_usage.h"
#include "load_average.h"
#include "layout.h"

#define tamanho_buffer 150000

static int ev_handler(struct mg_connection *conn, 
                      enum mg_event ev) {
  char buffer[tamanho_buffer];
  buffer[0] = '\x0';

  switch (ev) {
    case MG_AUTH:
	return MG_MORE;
    case MG_REQUEST:
    //PAGE REQUEST
    //EVERY REQUEST, EITHER BY TYPING URL
    //OR CALL CSS OR JAVASCRIPT
    //ENABLE THIS FUNCTION
    //printf("[%d] %s\n", strlen(conn->uri), conn->uri);
	
	//IF THE URL IS THE NAME OF THE FUNCTIONS, THE MOONGOSE RETURNS THE HTML REFERS TO THEM
	if (strcmp (conn->uri, "/dinamic_versaoso") == 0){

		mg_send_header(conn, "Content-Type", "text/html");

		//ADDS INFORMATIONS O.S
		versaoso(buffer, sizeof(buffer));
		
		mg_printf_data(conn, buffer);
		return MG_TRUE;

	}

        if (strcmp (conn->uri, "/dinamic_numprocessos") == 0){

		mg_send_header(conn, "Content-Type", "text/html");

		//ADDS INFORMATIONS ABOUT THE CṔU USAGE
		cpu_resultado(buffer, sizeof(buffer));

		//ADDS INFORMATIONS ABOUT THE LOAD AVERAGE
		load_average(buffer, sizeof(buffer));

		//ADDS INFORMATIONS ON THE NUMBER OS PROCESSES RUNNING
		numprocessos(buffer, sizeof(buffer));
		
		mg_printf_data(conn, buffer);
		return MG_TRUE;
	}

        if (strcmp (conn->uri, "/dinamic_infomemoria") == 0){

		mg_send_header(conn, "Content-Type", "text/html");

		//ADDS INFORMATIONS FROM MEMORY RAM 
		infomemoria(buffer, sizeof(buffer));

		mg_printf_data(conn, buffer);
		return MG_TRUE;
	}

	if (strcmp (conn->uri, "/dinamic_bateria") == 0){

		mg_send_header(conn, "Content-Type", "text/html");

		//ADDS BATTERY INFORMATION
		bateria(buffer, sizeof(buffer));

		mg_printf_data(conn, buffer);
		return MG_TRUE;
	}

	//IF YOU HAVE NOTHING IN THE URL IT PEFORMS THIS TEXT, OTHERWISE EXECUTE THE URL
	if(strlen(conn->uri)<=1){
		mg_send_header(conn, "Content-Type", "text/html");

		segmento_inicial(buffer, sizeof(buffer));

		segmento_final(buffer, sizeof(buffer));

    		mg_printf_data(conn, buffer);

    		return MG_TRUE;
    	}
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server;

  // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "document_root", ".");
  mg_set_option(server, "listening_port", "8080");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&server);

  return 0;
}

