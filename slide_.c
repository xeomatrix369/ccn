#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
int n,r;
struct frame
{
char ack;
int data;
}
frm[10];
int sender(void);
void recvack(void);
void resend_sr(void);
void resend_gb(void);
void goback(void);
void selective(void);
int main ()
{
int c;
do
{
printf("\n\n 1. selective repeat ARQ\n 2. goback arq\n 3.exit from he option\n");
printf("\n enter your choice");
scanf("%d",&c);
switch(c)
{
case 1: selective();
break;
case 2: goback();
break;
case 3:exit(0);
break;
}
}
while(c>=4);
return 0;
}
void goback()
{
sender();
recvack();
resend_gb();
printf("\n all frames sent successfully\n");
getch();
}
void selective()
{
sender();
recvack();
resend_sr();
printf("\n all frames sent successfully\n");
}
int sender()
{
int i;
printf("\n enter the number of frames to be sent");
scanf("%d",&n);
for(i=1;i<=n;i++)
{
printf("\n enter the data of frames[%d]",i);
scanf("%d",&frm[i].data);
frm[i].ack='y';
}
return 0;
}
void recvack()
{
int i;
rand();
r=rand()%n;
frm[r].ack='n';
for(i=1;i<=n;i++);
{
if (frm[i].ack=='n')
printf("\n the frame number %d is not received \n,r");
}
}
void resend_sr()
{
printf("\n resending frame %d",r);
sleep(2);
frm[r].ack='y';
printf("\n the received frame is %d", frm[r].data);
}
void resend_gb()
{
int i;
printf("\n resending fro.frame %d",r);
for(i=1;i<=n;i++);
{
sleep(2);
frm[i].ack='y';
printf("\n received data of frame %d is %d",i ,frm[i].data);
}
}