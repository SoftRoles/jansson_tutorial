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
    fprintf(stderr, "Error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  if (!json_is_array(root))
  {
    fprintf(stderr, "Error: string is not an json array\n");
    json_decref(root);
    return 1;
  }
  for (i = 0; i < json_array_size(root); i++)
  {
    json_t *object, *keyval;

    object = json_array_get(root, i);
    if (!json_is_object(object))
    {
      fprintf(stderr, "Error: json string is not an object\n");
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

  // read json file
  char *buf;
  char filename[80] = "object.json";
  printf("\n- JSON file read: \'%s\'.\n", filename);
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Failed: ");
    return 1;
  }
  root = json_loadf(file, 0, &error);
  fclose(file);
  if (!root)
  {
    fprintf(stderr, "Error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  if (json_is_array(root))
  {
    printf("File includes JSON array.\n");
  }
  else if (json_is_object(root))
  {
    printf("File includes JSON object.\n");
  }
  else
  {
    fprintf(stderr, "File includes non-JSON string.\n");
  }
  buf = json_dumps(root, JSON_INDENT(2));
  json_decref(root);
  printf("%s", buf);
  file = fopen("written.json", "w+");
    if (file != NULL)
    {
        fputs(buf, file);
        fclose(file);
    }
  free(buf);
  return 0;
}