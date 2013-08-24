#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 50
#define MAX_NUMBER 100
#define HISTOGRAM_SCALE 10


typedef struct historgram_data{
    int deficient;
    int perfect;
    int abundant;
} histogram_data;


void generate_random_numbers(unsigned int*, size_t);
unsigned int sum_of_divisors(unsigned int);
histogram_data process_number_list(unsigned int*, size_t);
histogram_data convert_to_scale_percentile(histogram_data, int, size_t);
void draw_histogram(histogram_data, char*, char*);

int main(int argc, char** argv){
    unsigned int num_list[MAX_SIZE];
    histogram_data actual_data;
    histogram_data scaled_data;


    generate_random_numbers(num_list, MAX_SIZE);
    actual_data=process_number_list(num_list, MAX_SIZE);
    scaled_data=convert_to_scale_percentile(actual_data,HISTOGRAM_SCALE,MAX_SIZE);

    printf("--- actual counts ---\n");
    printf("deficient :: %d\nperfect :: %d\nabundant :: %d\n",
           actual_data.deficient,actual_data.perfect,actual_data.abundant);
    printf("\n\n");
    printf("--- percentile counts (in %d scale) ---\n",HISTOGRAM_SCALE);
    printf("deficient :: %d\nperfect :: %d\nabundant :: %d\n",
           scaled_data.deficient,scaled_data.perfect,scaled_data.abundant);

    draw_histogram(scaled_data," * ","   ");

    return 0;
}

void draw_histogram(histogram_data data, char* histogram_char, char* blank_char){
    printf("\n\n");
    printf("--- drawing histogram ---\n");
    printf("\ndeficient: ");
    for(int ii=0;ii<data.deficient;ii++){
        printf(histogram_char);
    }
    printf("\nperfect  : ");
    for(int ii=0;ii<data.perfect;ii++){
        printf(histogram_char);
    }
    printf("\nabundant : ");
    for(int ii=0;ii<data.abundant;ii++){
        printf(histogram_char);
    }
    printf("\n\n\n");

    int max = data.deficient;
    if (data.perfect>max){
        max=data.perfect>max;
    }
    if (data.abundant>max){
        max=data.abundant;
    }
    for(int ii=max;ii>0;ii--){
        printf(ii<=data.deficient?histogram_char:blank_char);
        printf(ii<=data.perfect?histogram_char:blank_char);
        printf(ii<=data.abundant?histogram_char:blank_char);
        printf("\n");
    }
    printf(" D  P  A \n");
}


histogram_data convert_to_scale_percentile(histogram_data data, int scale, size_t sample_size){
    histogram_data retdata=data;
    retdata.deficient = round((((float)data.deficient/sample_size)*100)/scale);
    retdata.perfect = round((((float)data.perfect/sample_size)*100)/scale);
    retdata.abundant = round((((float)data.abundant/sample_size)*100)/scale);

    return retdata;
}


void generate_random_numbers(unsigned int* arr, size_t size){
    srand(time(NULL));
    for(size_t ii=0; ii<size; ii++){
        arr[ii]=(rand()%MAX_NUMBER)+1;
    }
}

unsigned int sum_of_divisors(unsigned int number){
    unsigned int sum=0;
    if (number>0){
        for (size_t ii=1; ii<=number/2; ii++){
            if(number%ii==0){
                sum+=ii;
            }
        }
    }
    return sum;
}


histogram_data process_number_list(unsigned int* arr, size_t size){
    histogram_data data = {.deficient=0, .perfect=0, .abundant=0};

    for (size_t ii=0;ii<size;ii++){
        unsigned int sumDivisor=sum_of_divisors(arr[ii]);
        int check = sumDivisor - arr[ii];
        if (check==0){
            data.perfect++;
        }else if (check>0){
            data.abundant++;
        }else{
            data.deficient++;
        }
    }
    return data;
}
