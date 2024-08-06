#include<stdio.h>
#include<string.h>
int main(){
    //declaring variables
    int i,j,keylen,msglen,flag=0;
    char input[100],key[30],temp[30],quot[100],rem[30],key1[30],temp1[30];
    // base data input
    printf("enter the data :");
    scanf("%s",input);
    //key generated using polynomials
    printf("enter the key :");
    scanf("%s",key);
    //length of key and input
    keylen=strlen(key);
    msglen=strlen(input);
    //alternalte copy of key
    strcpy(key1,key);
    //appending input with zeros of lenght key-1
    for(int i=0;i<keylen-1;i++){
        input[msglen+i]='0';
    }
    //storing temp for division
    for(i=0;i<keylen;i++){
        temp[i]=input[i];
    }
    //division block
    for(i=0;i<msglen;i++){
        quot[i]=temp[0];
        if(quot[i]=='0')
            for(j=0;j<keylen;j++)
                key[j]='0';
        else
            for(j=0;j<keylen;j++)
                key[j]=key1[j];
        //xoring temp and key
        for(j=keylen-1;j>0;j--){
            if(temp[j]==key[j])
                rem[j-1]='0';
            else
                rem[j-1]='1';
        }
        rem[keylen-1]=input[i+keylen];
        //updating temp as remainder
        strcpy(temp,rem);
                
    }
    // last temp is remainder
    strcpy(rem,temp);
    //printing quotient and remainder
    printf("\nQuotient is:");
    for(i=0;i<msglen;i++)
        printf("%c",quot[i]);
    printf("\nRemainder is: ");
    for(i=0;i<keylen-1;i++)
        printf("%c",rem[i]);
    // final data is msg followed by temp1
    printf("\nFinal data is:");
    for(i=0;i<msglen;i++)
        printf("%c",input[i]);
    for(i=0;i<keylen-1;i++)
        printf("%c",rem[i]);
    //-----------------reciever end---------------------------------//
    // taking recieved data
    printf("\nenter received the data :");
    scanf("%s",temp1);
    for(i=0;i<keylen;i++){
        temp[i]=temp1[i];
    }
    for(i=0;i<msglen;i++){
        quot[i]=temp[0];
        if(quot[i]=='0')
            for(j=0;j<keylen;j++)
                key[j]='0';
        else
            for(j=0;j<keylen;j++)
                key[j]=key1[j];
        for(j=keylen-1;j>0;j--){
            if(temp[j]==key[j])
                rem[j-1]='0';
            else
                rem[j-1]='1';
        }
        rem[keylen-1]=temp1[i+keylen];
        strcpy(temp,rem);
                
    }
    strcpy(rem,temp);
    //output quotend and remainder
    printf("\nQuotient is:");
    for(i=0;i<msglen;i++)
        printf("%c",quot[i]);
    printf("\nRemainder is: ");
    for(i=0;i<keylen-1;i++)
        printf("%c",rem[i]);

    flag=0;
    //check remainder is zero
    for(i=0;i<keylen-1;i++){
        if(rem[i]=='1'){
            flag=1;
            break;
        }
        else{
            flag=0;
        }
    }
    if(flag==0)
        printf("\nNo Error");
    else
        printf("\nError is detected");
    return 0; 

}