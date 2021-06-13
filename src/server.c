#include <stdio.h>
#include <ulfius.h>
#include <jansson.h>


#define PORT 8537
#define PREFIX "/api"

int callback_get_data(const struct _u_request *request, 
    struct _u_response *response, void *user_data)
{
  json_t * body_res = json_object();
  json_object_set(body_res, "medicion", json_integer(50));
  ulfius_set_json_body_response(response, MHD_HTTP_OK, body_res);
  return U_CALLBACK_CONTINUE;
}


int main()
{
  int retval; // Para guardar valores de retorno

  /* Seteo de numero de puerto para el framework */
  struct _u_instance instance; // Para inicializar el framework ulfius
  if (ulfius_init_instance(&instance, PORT, NULL, NULL))
  {
    exit(EXIT_FAILURE);
  }
  instance.max_post_body_size = 1024;
  // Endpoints
  ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/data", 0,
                             &callback_get_data, NULL);

  // Inicializar el framework
  retval = ulfius_start_framework(&instance); // Abre conexion http
  if (retval == U_OK)
  {
    pause();
  }
  else
  {
    fprintf(stderr, "ulfius_start_framework\n");
    exit(EXIT_FAILURE);
  }

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
  return 0;
}

