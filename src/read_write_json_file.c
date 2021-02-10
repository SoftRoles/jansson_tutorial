#include <stdio.h>
#include <string.h>
#include <jansson.h>

void read_write_json_file()
{
  fprintf(stdout, "\n- Read & Write JSON File\n");
  json_t *json, *json1, *json2, *json3, *json4, *njson;
  json_error_t error;

  char *bufc;
  char filename[80] = "object.json";
  fprintf(stdout, "-- Reading file: \'%s\'... ", filename);
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Failed.");
    fclose(file);
    exit(1);
  }
  fprintf(stdout, "Passed.");
  fprintf(stdout, "\n-- Parsing file contents ... ");
  json = json_loadf(file, 0, &error);
  if (!json)
  {
    fprintf(stderr, "Failed: on line %d: %s", error.line, error.text);
    exit(1);
  }
  fprintf(stdout, "Passed.");
  fclose(file);

  fprintf(stdout, "\n-- Check for valid json ... ");
  if (!json_is_array(json) && !json_is_object(json))
  {
    fprintf(stdout, "Failed.");
    json_decref(json);
    exit(1);
  }
  fprintf(stdout, "Passed.");

  fprintf(stdout, "\n-- Check wheter array or object ... ");
  if (json_is_array(json))
  {
    fprintf(stdout, "Array.");
  }
  else
  {
    fprintf(stdout, "Object.");
  }

  if (json_is_array(json))
  {
    fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. Before: \n");
    json1 = json_array_get(json, 0);
    bufc = json_dumps(json1, JSON_INDENT(2));
    printf("%s", bufc);
    free(bufc);
    fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. Checking if first element is object ... ");
    if (json_is_object(json1))
    {
      fprintf(stdout, "Passed.");
      fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. Checking if key value is string ... ");
      json2 = json_object_get(json1, "id");
      if (json_is_string(json2))
      {
        fprintf(stdout, "Passed.");
      }
      else
      {
        fprintf(stdout, "Failed.");
        json_decref(json);
        exit(1);
      }
      fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. Setting new value ... ");
      json3 = json_string("abcde");
      if (json_object_set(json1, "id", json3) == -1)
      {
        fprintf(stdout, "Failed.");
        json_decref(json);
        exit(1);
      }
      fprintf(stdout, "Passed.");
      fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. After: \n");
      bufc = json_dumps(json1, JSON_INDENT(2));
      printf("%s", bufc);
      free(bufc);

      fprintf(stdout, "\n-- Edit json ... Editing first element's key 'id'. Write to new file ... ");
      bufc = json_dumps(json, JSON_INDENT(2));
      file = fopen("written.json", "w+");
      if (file == NULL)
      {
        fprintf(stdout, "Failed.");
        json_decref(json);
        json_decref(json1);
        json_decref(json2);
        json_decref(json3);
        exit(1);
      }
      fputs(bufc, file);
      fprintf(stdout, "Passed.");
      fclose(file);
      free(bufc);
    }
    else
    {
      fprintf(stdout, "Failed.");
      json_decref(json);
      json_decref(json1);
      json_decref(json2);
      json_decref(json3);
      exit(1);
    }
  }
  else
  {
    fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ...");
    bufc = json_dumps(json1, JSON_INDENT(2));
    printf("%s", bufc);
    free(bufc);
    fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz' ...");
    json1 = json_object_get(json, "quiz");
    if (!json_is_object(json1))
    {
      fprintf(stdout, "Failed.");
      json_decref(json);
      exit(1);
    }
    fprintf(stdout, "Passed.");
    fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz.sport' ...");
    json2 = json_object_get(json1, "sport");
    if (!json_is_object(json2))
    {
      fprintf(stdout, "Failed.");
      json_decref(json);
      exit(1);
    }
    fprintf(stdout, "Passed.");
    fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz.sport.q1' ...");
    json3 = json_object_get(json2, "q1");
    if (!json_is_object(json3))
    {
      fprintf(stdout, "Failed.");
      json_decref(json);
      exit(1);
    }
    fprintf(stdout, "Passed.");
    fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check key value 'quiz.sport.q1.question' ...");
    json3 = json_object_get(json2, "q1");
    if (!json_is_object(json3))
    {
      fprintf(stdout, "Failed.");
      json_decref(json);
      exit(1);
    }
    fprintf(stdout, "Passed.");
  }
  // bufc = json_dumps(json, JSON_INDENT(2));
  // printf("%s", bufc);
  free(bufc);
  json_decref(json);
  json_decref(json1);
  json_decref(json2);
  json_decref(json3);
  // file = fopen("written.json", "w+");
  // if (file != NULL)
  // {
  //   fputs(bufc, file);
  //   fclose(file);
  // }
  // free(bufc);
  // return 0;
}