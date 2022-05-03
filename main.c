#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>

#define MAX_STRING_SIZE 256


#define DIE(assertion, call_description)				\
        do {								\
                if (assertion) {					\
                        fprintf(stderr, "(%s, %d): ",			\
                                        __FILE__, __LINE__);		\
                        perror(call_description);			\
                        exit(errno);					\
                }							\
        } while (0)

typedef struct head
{
    unsigned char type; // tipul de date stocate
    unsigned int len;   // lungimea totala
} head;                 // structura header
 
typedef struct data_structure
{
    head *header; // header-ul datelor
    void *data;   // datele efective
} data_structure; // structura de pasare a datelor
 
data_structure *insert_command(char *token, void **array)
{
    // aloc structura si headerul, avand o dimensiune cunoscuta
    data_structure *new_data = malloc(sizeof(*new_data));
    DIE(!new_data, "failed malloc");

    new_data->header = malloc(sizeof(head));
    DIE(!new_data->header, "failed malloc");
 
    // initializez lungimea
    new_data->header->len = sizeof(unsigned char) + sizeof(unsigned int);
 
    // get type
    token = strtok(NULL, " \n");
    memcpy(&new_data->header->type, token, sizeof(unsigned char));
 
    // get first_name
    token = strtok(NULL, " \n");
    char *first_name = malloc(strlen(token) + 1);
    DIE(!first_name, "failed malloc");
    memcpy(first_name, token, strlen(token) + 1);
    new_data->header->len += strlen(token) + 1;
 
    // 3 cazuri de int
	if(new_data->header->type == '1')
	{
    //get first banknote
    token = strtok(NULL, " \n");
    int8_t first_banknote = atoi(token);
    new_data->header->len += sizeof(int8_t);
 
    //get second banknote
    token = strtok(NULL, " \n");
    int8_t second_banknote = atoi(token);
    new_data->header->len += sizeof(int8_t);
 
    // get second_name
    token = strtok(NULL, " \n");
    char *second_name = malloc(strlen(token) + 1);
    DIE(!second_name, "failed malloc");
    memcpy(second_name, token, strlen(token) + 1);
    new_data->header->len += strlen(token) + 1;
 
    // aloc data
    new_data->data = malloc(new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    DIE(!new_data->data, "failed malloc");
    unsigned int pos = 0;
 
    memcpy(new_data->data, first_name, strlen(first_name) + 1);
    pos += strlen(first_name) + 1;
 
    memcpy(new_data->data + pos, &first_banknote, sizeof(int8_t));
    pos += sizeof(int8_t);
 
    memcpy(new_data->data + pos, &second_banknote, sizeof(int8_t));
    pos += sizeof(int8_t);
 
    memcpy(new_data->data + pos, second_name, strlen(second_name) + 1);
    pos += strlen(second_name) + 1;

	free(second_name);

	} else if(new_data->header->type == '2')
	{
    //get first banknote
    token = strtok(NULL, " \n");
    int16_t first_banknote = atoi(token);
    new_data->header->len += sizeof(int16_t);
 
    //get second banknote
    token = strtok(NULL, " \n");
    int32_t second_banknote = atoi(token);
    new_data->header->len += sizeof(int32_t);
 
    // get second_name
    token = strtok(NULL, " \n");
    char *second_name = malloc(strlen(token) + 1);
    DIE(!second_name, "failed malloc");
    memcpy(second_name, token, strlen(token) + 1);
    new_data->header->len += strlen(token) + 1;
 
    // aloc data
    new_data->data = malloc(new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    DIE(!new_data->data, "failed malloc");
    unsigned int pos = 0;
 
    memcpy(new_data->data, first_name, strlen(first_name) + 1);
    pos += strlen(first_name) + 1;
 
    memcpy(new_data->data + pos, &first_banknote, sizeof(int16_t));
    pos += sizeof(int16_t);
 
    memcpy(new_data->data + pos, &second_banknote, sizeof(int32_t));
    pos += sizeof(int32_t);
 
    memcpy(new_data->data + pos, second_name, strlen(second_name) + 1);
    pos += strlen(second_name) + 1;
	free(second_name);
	} else
	{
    //get first banknote
    token = strtok(NULL, " \n");
    int32_t first_banknote = atoi(token);
    new_data->header->len += sizeof(int32_t);
 
    //get second banknote
    token = strtok(NULL, " \n");
    int32_t second_banknote = atoi(token);
    new_data->header->len += sizeof(int32_t);
 
    // get second_name
    token = strtok(NULL, " \n");
    char *second_name = malloc(strlen(token) + 1);
    DIE(!second_name, "failed malloc");
    memcpy(second_name, token, strlen(token) + 1);
    new_data->header->len += strlen(token) + 1;
 
    // aloc data
    new_data->data = malloc(new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    DIE(!new_data->data, "failed malloc");
    unsigned int pos = 0;
 
    memcpy(new_data->data, first_name, strlen(first_name) + 1);
    pos += strlen(first_name) + 1;
 
    memcpy(new_data->data + pos, &first_banknote, sizeof(int32_t));
    pos += sizeof(int32_t);
 
    memcpy(new_data->data + pos, &second_banknote, sizeof(int32_t));
    pos += sizeof(int32_t);
 
    memcpy(new_data->data + pos, second_name, strlen(second_name) + 1);
    pos += strlen(second_name) + 1;
	free(second_name);
	}
	
	free(first_name);
    return new_data;
}
 
int add_last(void **array, int *len, data_structure *new_data)
{
     // len !=0 realloc
    if (*len != 0)
    {
        // parcurg tot vectorul ca sa ajung la ultimul element
		void *iterator = *array;
        int offset = sizeof(unsigned char);
		int len_elem = 0;
        for (int i = 0; i < *len; i++)
        {
			len_elem = *(unsigned int *)(iterator + offset);
			offset += len_elem;
        }

		offset -=sizeof(unsigned char);
        *array = realloc(*array, offset + new_data->header->len);
        DIE(!array, "failed malloc");
        
		int pos = 0;
        memcpy((*array + offset), &new_data->header->type, sizeof(unsigned char));
		pos += sizeof(unsigned char);
        memcpy((*array + pos + offset), &new_data->header->len, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy((*array + pos + offset), new_data->data, new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    }
    else    // len == 0 malloc
    {
        *array = malloc(new_data->header->len);
        DIE(!array, "failed malloc");
        
		int pos = 0;
        memcpy(*array, &new_data->header->type, sizeof(unsigned char));
		pos += sizeof(new_data->header->type);
        memcpy(*array + pos, &new_data->header->len, sizeof(new_data->header->len));
		pos += sizeof(new_data->header->len);
        memcpy(*array + pos, new_data->data, new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    }
 
	free(new_data->header);
	free(new_data->data);
	free(new_data);
    // incrementez nr de elemente
    (*len)++;
 
    return 0;
}
 
 
int add_at(void **array, int *len, data_structure *new_data, int index)
{
    if (index < 0)
    {
        return -1;
    }
    if (index > *len)
    {
        add_last(array, len, new_data);
		return 0;
    }

    // len !=0 realloc
    if (*len != 0)
    {
        // parcurg tot vectorul ca sa ajung la ultimul element
		void *iterator = *array;
        int offset1 = sizeof(unsigned char);
		int len_elem = 0;
        for (int i = 0; i < *len; i++)
        {
			len_elem = *(unsigned int *)(iterator + offset1);
			offset1 += len_elem;
        }
		offset1 -= sizeof(unsigned char);

        *array = realloc(*array, offset1 + new_data->header->len);
        DIE(!array, "failed malloc");
		iterator = *array;
		//shiftez
		int offset2 = sizeof(unsigned char);
		len_elem = 0;
		for (int i = 0; i < index; i++)
        {
			len_elem = *(unsigned int *)(iterator + offset2);
			offset2 += len_elem;
        }
		offset2 -= sizeof(unsigned char);

		memmove((iterator + offset2 + new_data->header->len), (iterator + offset2), offset1 - offset2);

		int pos = 0;
        memcpy((*array + offset2), &new_data->header->type, sizeof(unsigned char));
		pos += sizeof(unsigned char);
        memcpy((*array + pos + offset2), &new_data->header->len, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy((*array + pos + offset2), new_data->data, new_data->header->len - sizeof(unsigned int) - sizeof(unsigned char));
    
    }
    else 
    {
        add_last(array, len, new_data);
        return 0;
    }
 
    // incrementez nr de elemente
    (*len)++;

	free(new_data->header);
	free(new_data->data);
	free(new_data);
 
    return 0;
}
 
void find_command(void *data_block, int len, int index)
{
	if(index < 0 || index > len) 
	{
		return;
	}

	int offset = sizeof(unsigned char);
	char *iterator = data_block;
	int len_elem = 0;
	for(int i= 0 ; i < index; i++)
	{
		len_elem = *(unsigned int *)(iterator + offset);
		offset += len_elem;		
	}
	offset -= sizeof(unsigned char);

	char *type = malloc(sizeof(unsigned char));
    DIE(!type, "failed malloc");
	memcpy(type, (iterator + offset), sizeof(unsigned char));

    //print type
    printf("Tipul %c\n", *type);
	offset += sizeof(unsigned char) + sizeof(unsigned int);

 	char *toky;
	toky = strtok(iterator + offset, "\0");
    char *first_name = malloc((strlen(toky) + 1) * sizeof(char));
    DIE(!first_name, "failed malloc");

    memcpy(first_name, toky, (strlen(toky) + 1) * sizeof(char));
    offset += strlen(first_name) + 1;

	if(*type == '1')
		{
        int8_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int8_t));
        offset += sizeof(int8_t);
 
        int8_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int8_t));
        offset += sizeof(int8_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");

        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId8"\n", banknote1);
		printf("%"PRId8"\n\n", banknote2);

		free(second_name);
		} else if( *type == '2')
		{
        int16_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int16_t));
        offset += sizeof(int16_t);
 
        int32_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");

        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId16"\n", banknote1);
		printf("%"PRId32"\n\n", banknote2);

		free(second_name);
		} else 
		{
        int32_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        int32_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");

        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId32"\n", banknote1);
		printf("%"PRId32"\n\n", banknote2);
		free(second_name);
		}
    
	free(type);
	free(first_name);

}
 
int delete_at(void **array, int *len, int index)
{
    if (index < 0)
    {
        return -1;
    }
    if (index > *len)
    {
		return -2;
    }
        // parcurg tot vectorul ca sa ajung la ultimul element
		//final
		void *iterator = *array;
        int offset_final = sizeof(unsigned char);
		int len_elem = 0;
        for (int i = 0; i < *len; i++)
        {
			len_elem = *(unsigned int *)(iterator + offset_final);
			offset_final += len_elem;
        }
		offset_final -= sizeof(unsigned char);

		//initial
		iterator = *array;
        int offset_initial = sizeof(unsigned char);
		len_elem = 0;
        //<=index sau <index?
        for (int i = 0; i < index; i++)
        {
			len_elem = *(unsigned int *)(iterator + offset_initial);
			offset_initial += len_elem;
        }
		offset_initial -= sizeof(unsigned char);

		//mijloc
		int len_xxx = *(unsigned int*)(iterator + offset_initial + sizeof(unsigned char));

	memmove(iterator + offset_initial, iterator + offset_initial + len_xxx, offset_final - offset_initial - len_xxx);

	*array = realloc(*array, offset_final - len_xxx);
    DIE(!array, "failed malloc");

	(*len)--;

	return 0;
}
 
void print_command(void **array, int *len)
{
    int offset = 0;
    void *iterator = *array;
    for (int i = 0; i < *len; i++)
    {
        char *type = malloc(sizeof(char));
        DIE(!type, "failed malloc");

		memcpy(type, iterator + offset, sizeof(char));
 
        printf("Tipul %c\n", *type);
		offset = offset + sizeof(char);

		
		unsigned int *data_len = malloc(sizeof(unsigned int));
        DIE(!data_len, "failed malloc");

		memcpy(data_len, iterator + offset, sizeof(unsigned int));
		offset = offset + sizeof(unsigned int);

        char *toky;
		toky = strtok(iterator + offset, "\0");
        char *first_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!first_name, "failed malloc");
	
        memcpy(first_name, toky, (strlen(toky) + 1) * sizeof(char));
        offset += strlen(first_name) + 1;
 
        if(*type == '1')
		{
        int8_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int8_t));
        offset += sizeof(int8_t);
 
        int8_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int8_t));
        offset += sizeof(int8_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");
        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId8"\n", banknote1);
		printf("%"PRId8"\n\n", banknote2);
		

		free(second_name);
		} else if( *type == '2')
		{
        int16_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int16_t));
        offset += sizeof(int16_t);
 
        int32_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");
        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId16"\n", banknote1);
		printf("%"PRId32"\n\n", banknote2);
		free(second_name);
		} else 
		{
        int32_t banknote1;
        memcpy(&banknote1, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        int32_t banknote2;
        memcpy(&banknote2, iterator + offset, sizeof(int32_t));
        offset += sizeof(int32_t);
 
        toky = strtok(iterator + offset, "\0");
        char *second_name = malloc((strlen(toky) + 1) * sizeof(char));
        DIE(!second_name, "failed malloc");
        memcpy(second_name, toky,(strlen(toky) + 1) * sizeof(char));
        offset += strlen(second_name) + 1;
 
        printf("%s pentru %s\n", first_name, second_name);
		printf("%"PRId32"\n", banknote1);
		printf("%"PRId32"\n\n", banknote2);
		free(second_name);
		}

		free(first_name);
		free(type);
		free(data_len);
    }
}
 
void free_funct(void **array, int *len)
{
	if(*len)
	{
		free(*array);
	}
}
 
int main(void)
{
    void *array;
    char *command = malloc(MAX_STRING_SIZE);
    char *token;
    int *len = calloc(1, sizeof(int));
 
    while (1)
    {
        fgets(command, MAX_STRING_SIZE, stdin);
        token = strtok(command, " \n");
        if (strcmp(token, "insert") == 0)
        {
            data_structure *new_data = insert_command(token, &array);
            add_last(&array, len, new_data);
        }
        else if (strcmp(token, "insert_at") == 0)
        {
			token = strtok(NULL, " \n");
			int index = atoi(token);
			data_structure *new_data = insert_command(token, &array);
            add_at(&array, len, new_data, index);
        }
        else if (strcmp(token, "delete_at") == 0)
        {
			token = strtok(NULL, " \n");
			int index = atoi(token);
            delete_at(&array, len, index);
        }
        else if (strcmp(token, "find") == 0)
        {
			token = strtok(NULL, " \n");
			int index = atoi(token);
            find_command(array, *len, index);
        }
        else if (strcmp(token, "print") == 0)
        {
            print_command(&array, len);
        }
        else if (strcmp(token, "exit") == 0)
        {
            free_funct(&array, len);
            break;
        }
    }
	free(len);
    free(command);
    return 0;
}
