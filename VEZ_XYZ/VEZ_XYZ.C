#pragma GCC diagnostic ignored "-Wwrite-strings"
#define VERSION "В.Коротков (c) 1995, 2018  v1.0b"
/*------------------------ vez_xyz.c ----------------------*/
/*         Коротков В. (c) 1995, 2018 Екатеринбург         */
/*               Программа vez_xyz.exe                     */
/*---------------------------------------------------------*/
/* Программа преобразования ВЭЗ-файлов в текстовые файлы   */
/* для последующей передачи в программу SURFER, которая    */
/* создает матрицы на регулярной сетке, по которым можно   */
/* строить вертикальные карты сопротивлений                */
/*---------------------------------------------------------*/
/* Project  : vez_xyz.c                                    */
/* Model    : small                                        */
/* Library  :                                              */
/* Compiler : mingw-w64                                    */
/*---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

#include "vez_xyz.h"

/* ------------------------- Пpототипы ---------------------------*/

void out_help(char *hint);
void IndError(void);
void visa(void);
char *FindStringWithDelimiter(FILE *fp, char delim, char *str, int len,
                              char *brkstring);
int ScanFile(FILE *fp, char *str, int len, char *substr);
int ReadCurve(FILE *fp, VEZ *vez);
void out_error(char *msg);
int Check_VEZ_File(FILE *fp);
int get_info(FILE *in, PROFIL *pr);
int get_diapason(float min_val, float max_val, float *x0, int *Decades);

/* ----------------- ГЛОБАЛЬHЫЕ ПЕРЕМЕHHЫЕ ---------------------- */

#define DELIMITER 58 /* символ-разделитель ':' */
#define LEN 120      /* Длина вспомог. буфера */

char crv_begin[] = "#curve";  /* строка - признак начала кривой */
char crv_end[] = "#endcurve"; /* строка - признак конца кривой  */
char str[LEN];                /* Вспомог. буфер        */
char inname[64];              /* Имя входного ВЭЗ-файла */
FILE *inf;                    /* Входной VEZ - файл  */
char xyz_name[64];            /* Имя выходного XYZ-файла */
FILE *out;                    /* Выходной XYZ - файл */
int recno;                    /* Порядковый номер текущей кривой в VEZ-файле */

/*
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
▌                                                                 ▐
▌                M A I N                                          ▐
▌                                                                 ▐
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
*/
int main(int argc, char *argv[])
{
    PROFIL pr;   /* Описание профиля ВЭЗ   */
    VEZ vez;     /* Полная кривая ВЭЗ      */
    float Scale; /* Знаменатель масштаба, в котором планируется  */
                 /* построение вертикальной карты  сопротивлений */
    int i;

    visa();
    if (argc < 4)
    {
        IndError();
        out_help("Ошибка в командной строке !");
        return -1;
    }
    strcpy(inname, argv[1]); /* имя вх.файла - из командной строки */
    printf("\n ФАЙЛ %s\n", inname);
    strcpy(xyz_name, argv[2]); /* имя вых.файла - из командной строки */
    Scale = atof(argv[3]);     /* знамен. масштаба - из командной строки */

    if (NULL == (inf = fopen(inname, "rt")))
    {
        IndError();
        puts("Ошибка откpытия вх. файла !\n");
        return 1;
    }

    if (NULL == (out = fopen(xyz_name, "wt")))
    {
        IndError();
        printf("Ошибка откpытия вых. файла %s!\n", xyz_name);
        return 1;
    }

    if (Check_VEZ_File(inf))
    {
        IndError();
        printf("\7Входной файл %s не является VEZ-файлом!\n", inname);
        out_help("");
        return 1;
    }

    if (get_info(inf, &pr)) /* Пpочитать заголовок VEZ-файла */
        return 1;

    recno = 1;
    while (!ReadCurve(inf, &vez))
    {
        for (i = 0; i < vez.curve.n; i++)
        {
            fprintf(out, "%f %f %f\n",
                    vez.X, -(log10(vez.curve.AB2[i] / vez.curve.AB2[0]) * Scale / 25), vez.curve.fRok[i]);
        }
        ++recno;
        if (ferror(out)) /* Если была ошибка записи в файл */
        {
            IndError();
            puts("\7\7Ошибка записи на диск !");
            return 1;
        }
    }

    _fcloseall();
    return 0;
}

/* -----------------------------------------------------------
   visa
--------------------------------------------------------------*/
void visa(void)
{
    char cpyright[] =
        "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\r"
        "▌           Программа  vez_xyz                                    ▐\n\r"
        "▌ Преобразование профилей ВЭЗ в XYZ-файлы                         ▐\n\r"
        "▌           В.Коротков (c) 1995,2018                              ▐\n\r"
        "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n\r";
    puts(cpyright);
    puts(VERSION);
}

/*-------------------------------------------------------------------------
   FindStringWithDelimiter Функция ищет в файле fp строку,
   содержащую символ-разделитель delim. При этом работа начинается
   с текущей позиции в этом файле. Строки считываются во внешний
   буфер str размером len байт. Перед поиском разделителя производится
   коррекция каждой считанной строки путем вставки вместо символов ';'
   (комментариев) нулевых символов. Поиск заканчивается, если разделитель
   обнаружен. В этом случае функция возвращает указатель на символ в
   cтроке, идущий сразу за разделителем. При достижении конца файла или
   при ошибке возвращается NULL. Если в строке обнаружена подстрока,
   указанная в brkstring, то происходит прекращение поиска и выход
   с кодом NULL
---------------------------------------------------------------------------*/
char *FindStringWithDelimiter(FILE *fp, char delim, char *str, int len, char *brkstring)
{
    char *ptr;

    do
    {
        str[0] = 0;
        fgets(str, len, fp);    /* читаем строку */
        ptr = strchr(str, ';'); /* Ищем символ начала комментария */
        if (ptr)
            *ptr = 0;             /* Вставляем вместо него конец строки */
        ptr = strchr(str, delim); /* Ищем символ - разделитель */
        if (ptr)
            return ++ptr; /* Если есть - выход */
        if (strstr(str, brkstring))
            return NULL;
    } while ((!feof(fp)) && (!ferror(fp)));

    return NULL; /* ошибка или конец файла */
}

/* ------------------------------------------------------------
   get_info Пpочитать информационные заголовоки VEZ-файла in
   и заполнить стpуктуpу pr.
   Возвpащает 1 пpи ошибке, иначе 0
---------------------------------------------------------------*/
int get_info(FILE *in, PROFIL *pr)
{
#define LEN 120
    int n;
    float d;
    char *ptr;
    char str[LEN];
    pr->areaname[39] = 0;
    pr->profname[19] = 0;

    /* ищем  имя участка  */
    if (NULL == (ptr = FindStringWithDelimiter(in, DELIMITER, str, LEN, crv_begin)))
    {
        IndError();
        puts("\7Имя участка не найдено !\n");
        return 1;
    }

    strncpy(pr->areaname, ptr, 39); /* Имя участка */
    printf(" УЧАСТОК : %s\n", pr->areaname);
    puts("--------------------------------------------------------------------");

    /* ищем  имя профиля  */
    if (NULL == (ptr = FindStringWithDelimiter(in, DELIMITER, str, LEN, crv_begin)))
    {
        IndError();

        puts("\7Имя профиля не найдено !\n");
        return 1;
    }
    strncpy(pr->profname, ptr, 19); /* Имя участка */
    printf(" ПРОФИЛЬ : %s\n", pr->profname);

    return 0;
}

/*-------------------------------------------------------------------------
   ScanFile Функция просматривает строки файла fp строку, начиная с текущей
   позиции, на предмет обнаружения подстроки substr. Строки считываются во
   внешний буфер str размером len байт. Перед поиском производится
   коррекция каждой считанной строки путем вставки вместо символов ';'
   (комментариев) нулевых символов. Поиск заканчивается, если подстрока
   обнаружена. В этом случае функция возвращает 0. При достижении конца
   файла или при ошибке возвращается 1.
---------------------------------------------------------------------------*/
int ScanFile(FILE *fp, char *str, int len, char *substr)
{
    char *ptr;

    do
    {
        str[0] = 0;
        fgets(str, len, fp);    /* читаем строку */
        ptr = strchr(str, ';'); /* Ищем символ начала комментария */
        if (ptr)
            *ptr = 0; /* Вставляем вместо него конец строки */
        if (strstr(str, substr))
            return 0; /* подстрока найдена ! */
    } while ((!feof(fp)) && (!ferror(fp)));

    return 1; /* ошибка или конец файла */
}

/* ------------------------------------------------------------
   ReadCurve Пpочитать очередную кривую из ВЭЗ-файла fp и
   заполнить структуру vez. При ошибке возвращает код ошибки
   При достижении  конца файла возвращает 1.
   При успешном завершении возвращает 0.
---------------------------------------------------------------*/
int ReadCurve(FILE *fp, VEZ *vez)
{
    int code, cnt;
    long oldpos;
    char *ptr;
    float a, r, rmin, rmax;
    static int already = 0;
    static int recno = 0; /* номер записи */

    if (!already)
    {
        rewind(fp);
        already = 1;
    }

    ++recno;
    //    clrscr();
    vez->ID_curve[19] = 0;
    rmin = 10000000;
    rmax = 0;
    code = ScanFile(fp, str, LEN, crv_begin); /* Ищем признак начала кривой */
    if (code)
    {
        puts("\n <><> Кривых больше нет ... <><>\n");
        return 1;
    }
    oldpos = ftell(fp); /* запомним положение */

    code = ScanFile(fp, str, LEN, crv_end); /* Ищем признак конца кривой */
    if (code)
    {
        IndError();
        puts("\7Признак конца кривой не найден ...\n");
        return 1;
    }
    fseek(fp, oldpos, SEEK_SET); /* вернемся */

    /* ищем имя кривой */
    if (NULL ==
        (ptr = FindStringWithDelimiter(fp, DELIMITER, str, LEN, crv_end)))
    {
        IndError();
        puts("\7Имя кривой не найдено !\n");
        return 1;
    }
    strncpy(vez->ID_curve, ptr, 19); /* Имя кривой */
    printf(" Запись #%3d,  ВЭЗ : %s\n", recno, vez->ID_curve);
    /* ищем координаты */
    if (NULL ==
        (ptr = FindStringWithDelimiter(fp, DELIMITER, str, LEN, crv_end)))
    {
        IndError();
        puts("\7Координаты кривой не найдены !\n");
        return 1;
    }
    sscanf(ptr, "%f%f%f", &(vez->X), &(vez->Y), &(vez->Z));
    printf("Координаты : %8.1f %8.1f %8.1f\n", vez->X, vez->Y, vez->Z);

    /* теперь сами отсчеты */
    cnt = 0; /* счетчик отсчетов */
    do
    {
        str[0] = 0;
        fgets(str, LEN, fp);    /* читаем строку */
        ptr = strchr(str, ';'); /* Ищем символ начала комментария */
        if (ptr)
            *ptr = 0; /* Вставляем вместо него конец строки */
        if (strstr(str, crv_end))
            break; /* конец кривой найден ! */

        // code = sscanf(str, "%f%f", &a, &r); /* читаем */
        // if (code == 2)
        code = sscanf(str, "%f%f%f%f%f%f%f", &a, &r, &r, &r, &r, &r, &r); /* читаем */
        if (code == 7)
        {
            vez->curve.AB2[cnt] = a;
            vez->curve.fRok[cnt] = r;
            if (r < rmin)
                rmin = r;
            if (r > rmax)
                rmax = r;
            ++cnt;
        }
    } while (!ferror(fp));
    vez->curve.n = cnt;
    vez->first_absc = vez->curve.AB2[0];
    vez->RokMin = rmin;
    vez->RokMax = rmax;
    vez->AB2Min = vez->curve.AB2[0];
    vez->AB2Max = vez->curve.AB2[cnt - 1];

    get_diapason(vez->RokMin, vez->RokMax, &(vez->OrgRok), &(vez->RokDecads));
    get_diapason(vez->AB2Min, vez->AB2Max, &(vez->OrgAB2), &(vez->AB2Decads));

    for (cnt = 0; cnt < vez->curve.n; cnt++)
        printf("%3d  AB/2 = %8.1f  Rok = %8.1f\n",
               cnt + 1, vez->curve.AB2[cnt], vez->curve.fRok[cnt]);
    return 0;
}

/* ------------------------------------------------------------
   out_error Выводит на экран сообщение об ошибке
---------------------------------------------------------------*/
void out_error(char *msg)
{
    //    gotoxy(24, 40 - strlen(msg) / 2);
    puts(msg);
    getch();
}

/* -------------------------------------------------------------------
   out_help Выводит подсказку из строки hint и создает шаблон входного
   VEZ-файла
----------------------------------------------------------------------*/
void out_help(char *hint)
{
    char fname[] = "vez_xyz.hlp";
    FILE *out;

    printf("\7 %s\n\n"
           " Использование программы : vez_xyz.exe <VEZfile> <OutFile> <Scale>\n"
           "  где VEZfile - имя входного  файла формата VEZ,\n"
           "      OutFile - имя выходного XYZ-файла\n"
           "      Scale   - знаменатель  масштаба, в котором будет строиться карта\n"
           "Прмер оформления VEZ-файла смотрите в файле %s\n",
           hint, fname);

    if (NULL == (out = fopen(fname, "wt"))) /* откроем файл */
    {
        IndError();
        printf("\7Ошибка открытия файла %s для записи!\n", fname);
        return;
    }
    fprintf(out,
            "VEZFILE\n"
            ";=========================================================================\n"
            "; Структура файла формата VEZ для программы vez_xyz.exe. %s\n"
            ";-------------------------------------------------------------------------\n"
            "; Самыми ПЕРВЫМИ 7 символами в файле формата VEZ (vez-файле) должны быть\n"
            "; следующие символы: VEZFILE в любом регистре.\n"
            "; Символы кавычек служат началом комментариев - все символы\n"
            "; правее них и до конца строки игнорируются. Пустые строки допускаются.\n"
            ";   VEZ-файл должен содержать кривые для ОДНОГО участка и ОДНОГО профиля\n"
            "; Имена участка и профиля должны быть заданы в начале файла.\n"
            ";-------------------------------------------------------------------------\n"
            "Area   : Кыштым - Слюдорудник ; Участок\n"
            "Profil : Интерпр. 1           ; Профиль\n"
            ";-------------------------------------------------------------------------\n"
            "; Далее идут описания кривых - блоки данных, начинающиеся #curve\n"
            "; и заканчивающиеся #endcurve. В каждом блоке вначале задается имя\n"
            "; кривой (не более 20 симв. от ':' до конца строки, затем координаты\n"
            "; кривой X Y Z (3 числа типа float), затем задаются значения AB/2	MN/2	K	U	D	I	Rok\n"
            "; соответственно, причем каждая пара должна начинаться с новой строки. \n"
            "; ПРИМЕЧАНИЕ : отсчеты ОБЯЗАТЕЛЬНО должны даваться в порядке возрастания\n"
            "; разносов !\n"
            ";-------------------------------------------------------------------------\n"
            "#curve\n"
            "Кривая :	1\n"
            "Коорд. X Y Z :	0 0 0\n"
            ";AB/2\tMN/2\tK\t\tU\tD\tI\tRok\n"
            "1\t0,5\t2,3561925\t42\t1000\t10\t99\n"
            "1,5\t0,5\t6,28318\t\t46\t300\t10\t87\n"
            "2,2\t0,5\t14,4198981\t72\t100\t10\t104\n"
            "3\t0,5\t27,4889125\t42\t100\t10\t115\n"
            "5\t0,5\t77,7543525\t44\t30\t10\t103\n"
            "#endcurve\n"
            "#curve\n"
            "Кривая :	2\n"
            "Коорд. X Y Z :	0 0 0\n"
            ";AB/2\tMN/2\tK\t\tU\tD\tI\tRok\n"
            "1\t0,5\t2,3561925\t50\t1000\t10\t118\n"
            "1,5\t0,5\t6,28318\t\t65\t300\t10\t123\n"
            "2,2\t0,5\t14,4198981\t41\t300\t10\t177\n"
            "3\t0,5\t27,4889125\t78\t100\t10\t214\n"
            "5\t0,5\t77,7543525\t34\t100\t10\t264\n"
            "#endcurve\n");

    fclose(out);
    printf("\n\n Hажмите любую клавишу ...");
    getch(); /* Ждем-с */
    return;
}

/* -------------------------------------------------------------------
   Check_VEZ_File Проверяет VEZ-файл на корректность и возвращает не 0,
   если файл имеет некорректный заголовок.
   fp - указатель на проверяемый VEZ-файл.
   При  успешном завершении возвращает 0
----------------------------------------------------------------------*/
int Check_VEZ_File(FILE *fp)
{
    char signature[8];

    rewind(fp);
    signature[7] = 0;
    fread(signature, 7, 1, fp); /* первые 7 символов - сигнатура */
    strupr(signature);
    return strncmp(signature, "VEZFILE", 7); /* сигнатура VEZFILE */
}

/*--------------------------------------------
  IndError Выдает индикацию ошибки
---------------------------------------------- */
void IndError(void)
{
    //    textcolor(WHITE + 128);
    //    cprintf("\n\r****** ");
    printf("\n\r****** ");
    //    textcolor(LIGHTGRAY);
}

/* -------------------------------------------------------------------
   get_diapason Функция по заданному минимальному и максимальному
   значениям некоторой величины определяет количество логарифмических
   декад для отображения на логарифмическом бланке. Величина x0 - это
   точка отсчета логарифмической шкалы, кратная степени 10 ( 0.1, 1,
   10 и т.п.)
   При нормальном завершении функция возвращает 0, при ошибке 1.
   Ошибка - если значение min_val < 0.001 или max_val > 10**10
---------------------------------------------------------------------- */
int get_diapason(float min_val, float max_val, float *x0, int *Decades)
{
    int p;
    float v, a, b;

    if (min_val < 0.001)
        return 1;
    if (max_val > 1E10)
        return 1;

    p = (int)floor(log10(min_val));
    switch (p)
    {
    case -3:
        *x0 = 0.001;
        break;
    case -2:
        *x0 = 0.01;
        break;
    case -1:
        *x0 = 0.1;
        break;
    case 0:
        *x0 = 1;
        break;
    case 1:
        *x0 = 10;
        break;
    case 2:
        *x0 = 100;
        break;
    case 3:
        *x0 = 1E3;
        break;
    case 4:
        *x0 = 1E4;
        break;
    case 5:
        *x0 = 1E5;
        break;
    case 6:
        *x0 = 1E6;
        break;
    case 7:
        *x0 = 1E7;
        break;
    case 8:
        *x0 = 1E8;
        break;
    case 9:
        *x0 = 1E9;
        break;
    case 10:
        *x0 = 1E10;
        break;
    }

    p = (int)ceil(log10(max_val));
    switch (p)
    {
    case -3:
        v = 0.001;
        break;
    case -2:
        v = 0.01;
        break;
    case -1:
        v = 0.1;
        break;
    case 0:
        v = 1;
        break;
    case 1:
        v = 10;
        break;
    case 2:
        v = 100;
        break;
    case 3:
        v = 1E3;
        break;
    case 4:
        v = 1E4;
        break;
    case 5:
        v = 1E5;
        break;
    case 6:
        v = 1E6;
        break;
    case 7:
        v = 1E7;
        break;
    case 8:
        v = 1E8;
        break;
    case 9:
        v = 1E9;
        break;
    case 10:
        v = 1E10;
        break;
    }

    a = log10(v);
    b = log10(*x0);
    *Decades = (int)(a - b);

    return 0;
}