//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <Windows.h>
//#include <locale.h>
//#define N 500
//
//struct flights{
//    int num;                    
//    char dep[80];               
//    char app[80];               
//    int tdep[2];                
//    int tapp[2];                
//};
//
//void f_MyEnd();                 
//void New_Record();              
//void Delete();                  
//void Search1();                 
//void Search2();                 
//void List();                    
//void init_list();               
//int find_free();                
//int FlightTime(struct flights F);      
//
//struct flights *A;
//
//void main(){
//    setlocale(LC_ALL, "Rus");
//    FILE *f;
//
//    int a, d;                      
//    int PWork = 0;
//    PWork = atexit(f_MyEnd);
//    if(PWork != 0) puts("Ошибка регистрации функции\n");
//    A = (struct flights *)malloc(sizeof(struct flights)*N);
//    init_list();                                                
//
//    f = fopen("kurs10.txt", "r");
//    int i = 0;
//    while(1){                 
//        if(feof(f)) break;
//        fscanf(f, "%d", &A[i].num);
//        fscanf(f, "%s", &A[i].dep);
//        fscanf(f, "%s", &A[i].app);
//        fscanf(f, "%d%d", &A[i].tdep[0], &A[i].tdep[1]);
//        fscanf(f, "%d%d", &A[i].tapp[0], &A[i].tapp[1]);
//        i++;
//    }
//    fclose(f);
//
//    while(1){
//        printf("Выбирете команду\n");
//        printf("1. Новая запись\n");             
//        printf("2. Удалить запись\n");           
//        printf("3. Поиск записи\n");             
//        printf("4. Список записей\n");           
//        printf("5. Выход\n");                    
//        printf("Введите: ");
//        scanf("%d", &a);
//        switch (a){
//        case 1:
//            system("cls");
//            New_Record();
//            break;
//
//        case 2:
//            system("cls");
//            Delete();
//            break;
//
//        case 3:
//            printf("Что ищем?\n");
//            printf("1. Перелёт между пунктами\n");
//            printf("2. Три рейса\n");
//            printf("Введите: ");
//            scanf("%d", &a);
//            switch (a)
//            {
//            case 1:
//                system("cls");
//                Search1();
//                break;
//
//            case 2:
//                system("cls");
//                Search2();
//                break;
//
//            default:
//                printf("Неизвестная команда\n");
//                system("cls");
//                break;
//            }
//            break;
//
//        case 4:
//            system("cls");
//            List();
//            break;
//
//        case 5:
//            free(A);
//            _Exit(EXIT_SUCCESS);
//            break;
//
//        default:
//            printf("Неизвестная команда\n");
//            system("cls");
//            break;
//        }
//    }
//}
//
//void f_MyEnd(){
//    puts ("Успешный выход");
//}
//
//void New_Record(){
//    int slot;
//    slot = find_free();
//    if(slot==-1) {
//        printf("\n Список переполнен \n");
//        return;
//    }
//    printf("Введите номер рейса \n");
//    scanf("%d", &A[slot].num);
//    printf("Введите точку отправления \n");
//    scanf("%s", &A[slot].dep);
//    printf("Введите пункт назначения \n");
//    scanf("%s", &A[slot].app);
//    printf("Введите время отправления 00 00 \n");
//    scanf("%d%d", &A[slot].tdep[0], &A[slot].tdep[1]);
//    printf("Введите время прибытия 00 00 \n");
//    scanf("%d%d", &A[slot].tapp[0], &A[slot].tapp[1]);
//
//    system("cls");
//}
//
//void Delete(){
//    printf("Введите номер записи\n");
//    int d;
//    scanf("%d", &d);
//    if( (d >= 0)&&(d <= N) ) A[d].num = 0;       
//}
//
//void Search1(){
//    char d[60], a[60];
//    int n = 0;
//    printf("Доступные места:\n Peterburg\n Moscow\n Novosibirsk\n Minsk\n Sochi\n");
//    printf("Введите пункт отправления\n");               
//    scanf("%s", &d);
//    printf("Введите пункт назначения\n");             
//    scanf("%s", &a);
//    printf("\n");
//    printf("Рейсы между %s и %s (По московскому времени)\n\n", d, a);
//    for (int i = 0; i < N; i++)
//        if (A[i].num != 0)                              
//            if ((strcmp(A[i].dep, d) == 0) && (strcmp(A[i].app, a) == 0)){             
//                printf("%d\n", A[i].num);
//                printf("%s - ", A[i].dep);
//                printf("%s\n", A[i].app);
//                printf("%d:%d\n", A[i].tdep[0], A[i].tdep[1]);
//                printf("%d:%d\n", A[i].tapp[0], A[i].tapp[1]);
//                printf("\n");
//                n = 1;
//            }
//    if (n == 0) printf("Не найдено\n");
//}
//
//void Search2(){
//    char d[60];
//    int time = 0, in1 = 0, in2 = 0, in3 = 0;
//
//    printf("Введите пункт отправления\n");               
//    printf("Домтупные места:\n Санкт-Петербург\n Москва\n Новосибирск\n Минск\n Сочи\n");
//    scanf("%s", &d);
//    for (int i = 0; i < N; i++){
//        if ( (A[i].num != 0)&&( strcmp(A[i].dep, d) == 0 )){
//            if ( FlightTime(A[i]) > time ){
//                time = FlightTime(A[i]);
//                in3 = in2;
//                in2 = in1;
//                in1 = i;
//            }else if ( FlightTime(A[i]) > FlightTime(A[in2]) ){
//                in3 = in2;
//                in2 = i;
//            }else if ( FlightTime(A[i]) > FlightTime(A[in3]) ){
//                in3 = i;
//            }
//        }
//    }
//    printf("Три самых длинных рейса из %s (По московскому времени)\n", d);
//    printf("%d    %s - %s %d:%d   %d:%d\n", A[in1].num, A[in1].dep, A[in1].app, A[in1].tdep[0], A[in1].tdep[1], A[in1].tapp[0], A[in1].tapp[1]);
//
//    printf("%d    %s - %s %d:%d   %d:%d\n", A[in2].num, A[in2].dep, A[in2].app, A[in2].tdep[0], A[in2].tdep[1], A[in2].tapp[0], A[in2].tapp[1]);
//
//    printf("%d    %s - %s %d:%d   %d:%d\n", A[in3].num, A[in3].dep, A[in3].app, A[in3].tdep[0], A[in3].tdep[1], A[in3].tapp[0], A[in3].tapp[1]);
//}
//
//void List(){
//    int i, n = 1;
//    for ( i = 0; i < N; i++)
//        if (A[i].num != 0){
//            printf("%d.  ", n); n++;
//            printf("%10d\t  %19s - %s\t %10d:%d\t   %10d:%d\t\n", A[i].num, A[i].dep, A[i].app, A[i].tdep[0], A[i].tdep[1], A[i].tapp[0], A[i].tapp[1]);
//            
//        }
//    printf("\n\n");
//}
//
//void init_list(){                           
//  int i;
//  for( i = 0; i < N; i++)
//    A[i].num = 0;
//}
//
//int find_free(){
//    int i;
//    for( i = 0; (A[i].num != 0)&&(i<N); i++) ;     
//    if(i == N) return -1;           
//    return i;                       
//}
//
//int FlightTime(struct flights F){
//    int t, ta, td;
//    ta = F.tapp[0]*60 + F.tapp[1];           
//    td = F.tdep[0]*60 + F.tdep[1];
//    if(ta <= td){                        
//        if (ta == td) return 1440;          
//        else t = 1440 - (td-ta);                 
//    }
//    else{
//        t = ta - td;
//    }
//    return t;
//}
