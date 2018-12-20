//
// ves_rc.h - файл заголовков для программы VES for Windows
//            Здесь определяются константы для ресурсов WINDOWS


#define IDM_COMPUTE_TYPE_CURVE	912
#define IDM_COMPILE             911

#define VERSIONINFO_1           1
#define VERSION                 1200

//
// Диалоговое окно DLG_TYPE
//
#define IDC_EB_NLAYERS_TC	660
#define IDC_SB_NLAYERS_TC       661 // Число слоев (ScrollBar)

#define IDC_NSAMPLES	662
#define IDC_FIRSTABS	663
#define IDC_WRTOFILE	664
#define IDC_FRAME       665

// Edit Cопpотивления слоев.
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_R1	760
#define IDC_R2	761
#define IDC_R3	762
#define IDC_R4	763
#define IDC_R5	764
#define IDC_R6	765
#define IDC_R7	766
#define IDC_R8	767

// Edit Мощности слоев
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_H1          680
#define IDC_H2          681
#define IDC_H3          682
#define IDC_H4          683
#define IDC_H5          684
#define IDC_H6          685
#define IDC_H7          686


/* Идентификаторы меню */

#define IDM_OPEN                101
#define IDM_NEW                 102
#define IDM_SAVE                103
#define IDM_SAVE_AS             104
#define IDM_EXIT                105

#define IDM_MANUAL              750
#define IDM_AUTO                751


#define IDM_NEXT                900
#define IDM_PREV                901
#define IDM_FIRST               902
#define IDM_LAST                903
#define IDM_SAVECURVE           906
#define IDM_INFO                907

#define IDM_HELP                908
#define IDM_USING_HELP          909
#define IDM_ABOUT               910

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
//
//        Идентификаторы управляющих элементов
//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

// Диалоговое окно DLG_VES

#define IDC_EB_NLAYERS  200   // Число слоев Number of layers
#define IDC_SB_NLAYERS  201   // ScrollBar для Number of layers

#define IDT_CURVE_ID    170   // Имя кривой

// Edit Cопpотивления слоев.
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_EB_RESIS1   300   // Первый слой
#define IDC_EB_RESIS2   301
#define IDC_EB_RESIS3   302
#define IDC_EB_RESIS4   303
#define IDC_EB_RESIS5   304
#define IDC_EB_RESIS6   305

// ScrollBars для Cопpотивлений слоев
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_SB_RESIS1   400
#define IDC_SB_RESIS2   401
#define IDC_SB_RESIS3   402
#define IDC_SB_RESIS4   403
#define IDC_SB_RESIS5   404
#define IDC_SB_RESIS6   405

// Edit Мощности слоев
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_EB_THICK1   500
#define IDC_EB_THICK2   501
#define IDC_EB_THICK3   502
#define IDC_EB_THICK4   503
#define IDC_EB_THICK5   504

 // ScrollBars для Мощностей слоев
// Нужно следить, чтобы идентификаторы этих элементов ОБЯЗАТЕЛЬНО
// были последовательными с шагом +1 !!!
#define IDC_SB_THICK1   600
#define IDC_SB_THICK2   601
#define IDC_SB_THICK3   602
#define IDC_SB_THICK4   603
#define IDC_SB_THICK5   604

//        КHОПКИ
#define IDC_BU_SAVE     700  // Save
#define IDC_BU_PRINT    701  // Print
#define IDC_BU_NEXT     702  // Next
#define IDC_BU_PREV     703  // Prev
#define IDC_BU_FIND     704  // Find
#define IDC_CB_INTERPR  705   // Переключатель режима интерпретации

#define ID_BITMAP_VES   1000

// Элементы управления диалогового окна Info
#define IDT_RMS         180
#define IDT_FNAME       181
#define IDT_AREANAME    182
#define IDT_PROFNAME    183
#define IDT_CURVENAME   184
#define IDT_NSAMPLES    185
#define IDT_NCURVE      186
#define IDT_COORD       187

#define IDC_LB_FIELDDATA  620 // Список

			     // Данные о Модели
#define IDT_LAYER1      630  // Номера слоев
#define IDT_LAYER2      631
#define IDT_LAYER3      632
#define IDT_LAYER4      633
#define IDT_LAYER5      634
#define IDT_LAYER6      635

#define IDT_RESIS1      640  // Сопрот. слоев
#define IDT_RESIS2      641
#define IDT_RESIS3      642
#define IDT_RESIS4      643
#define IDT_RESIS5      644
#define IDT_RESIS6      645

#define IDT_THICK1      650  // Мощн. слов
#define IDT_THICK2      651
#define IDT_THICK3      652
#define IDT_THICK4      653
#define IDT_THICK5      654

#define id_bmp  110

// СООБЩЕНИЯ, ОПРЕДЕЛЯЕМЫЕ ПРОГРАММОЙ
#define WM_PROGRESS     0x500
