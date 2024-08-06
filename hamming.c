#include<stdio.h>
void main(){
    int data[10],rec[10],i,c,c1,c2,c3;
    printf("enter 4 bits of data one by one \n");
    scanf("%d%d%d%d",&data[3],&data[5],&data[6],&data[7]);
    data[1]=data[3]^data[5]^data[7];
    printf("Parity bit at P1,%d\n",data[1]);
    data[2]=data[3]^data[6]^data[7];
    printf("Parity bit at P2,%d\n",data[2]);
    data[4]=data[5]^data[6]^data[7];
    printf("Parity bit at P3,%d\n",data[4]);
    printf("\nEncoded data is \n");
    for(i=7;i>0;i--){
        printf("%d",data[i]);
    }
    printf("\n");
    printf("enter the recieved data bits one by one \n");
    for(i=0;i<7;i++)
        scanf("%d",&rec[i]);
    c1=rec[6]^rec[4]^rec[2]^rec[0];
    c2=rec[5]^rec[4]^rec[2]^rec[0];
    c3=rec[3]^rec[2]^rec[1]^rec[0];
    c=(c3*4)+(c2*2)+c1;
    if(c==0)
        printf("No error white transmission of data\n");
    else{
        printf("\nError on position\n %d",c);
        printf("\nData recieved : \n");
        for(i=0;i<7;i++) printf("%d",rec[i]);
        printf("\nencoded message is\n");
        if(rec[7-c]=0) rec[7-c]=1;
        else rec[7-c]=0;
        for(i=0;i<7;i++)
            printf("%d",rec[i]);

    }


}