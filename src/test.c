#include <stdio.h>
#include <stdlib.h>

int main (){
  int nb;
  printf("\nEntrez un nombre positif :");
  scanf("%d",&nb);
  if(nb<=0){
    printf("Veuillez entrer un nombre strictement positif.");
  }
  else{
    FILE *fp;
    fp= fopen("divisors.txt","w");
    fprintf(fp,"Les diviseurs de %d sont : \n",nb);
    for(int i = 1; i <= nb; i++) {
      if((nb%i) == 0){
        fprintf(fp,"%d\n",i);
        printf("%d\n",i);
      }
    }
    fclose(fp);
  }
  return 0;
}
