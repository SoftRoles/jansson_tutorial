#include <stdio.h>
#include <string.h>
#include <jansson.h>

int main()
{
  // parse json array
  size_t i;
  char text[1000] = "[{\"id\": \"a1\"},{\"id\": \"a2\"}]";

  json_t *root;
  json_error_t error;

  root = json_loads(text, 0, &error);
  if (!root)
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  if (!json_is_array(root))
  {
    fprintf(stderr, "error: string is not an json array\n");
    json_decref(root);
    return 1;
  }
  for (i = 0; i < json_array_size(root); i++)
  {
    json_t *object, *keyval;

    object = json_array_get(root, i);
    if (!json_is_object(object))
    {
      fprintf(stderr, "error: json string is not an object\n");
      json_decref(root);
      return 1;
    }
    keyval = json_object_get(object, "id");
    if (!json_is_string(keyval))
    {
      fprintf(stderr, "error: json key value is not a string\n");
      json_decref(root);
      return 1;
    }
    printf("id: %s\n", json_string_value(keyval));
  }
  json_decref(root);

  //construct json object
  json_t *keyval, *val;
  json_t *obj = json_object();
  val = json_string("Hüseyin");
  json_object_set(obj, "name", val);
  val = json_string("YİĞİT");
  json_object_set(obj, "surname", val);
  keyval = json_object_get(obj, "name");
  if (!json_is_string(keyval))
  {
    fprintf(stderr, "error: json key value is not a string\n");
    json_decref(root);
    return 1;
  }
  printf("name: %s\n", json_string_value(keyval));
  keyval = json_object_get(obj, "surname");
  if (!json_is_string(keyval))
  {
    fprintf(stderr, "error: json key value is not a string\n");
    json_decref(root);
    return 1;
  }
  printf("surname: %s\n", json_string_value(keyval));
  json_decref(obj);
  return 0;
}