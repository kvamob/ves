С====================================================================
C vez1.for
C Программа прямой интерпретации ВЭЗ
C О.Куфуд стр.211
C====================================================================      
C Программа последовательно задает следующие вопросы:
C   1. "Дать предел относительной погрешности". Обычно это 0.01-0.02
C   2. "Новые полевые данные ? Да=0". Если ответ отрицателен, то
C программа немедленно начинает вычисления.
C   3. "Дать значение первой абсциссы". Это абсцисса первой отсчетной 
C точки, вводимой в компьютер. Программа требует экстраполяции
C наблюденной кривой каж. сопротивления как влево, так и вправо.
C При экстраполяции влево должна быть достигнута абсцисса, которая 
C отличается от исходной по крайней мере в 2 раза. Программа выдает
C первый отсчет трансформанты сопротивления, абсцисса которого в
C 2.16 раза больше "значения первой абсциссы". Надо иметь в виду, что 
C удельное сопротивление первого слоя предполагается равным значению 
C кажущегося сопротивления в первой отсчетной точке.
C  4. "Дать число отсчетов"
C  5. "Дать число(значения) отсчетов". Отсчеты должны быть даны с шагом
C дискретизации 1/8 декады. Последний вводимый отсчет должен быть
C экстраполирован на расстояние, которое примерно в 8 раз больше
C абсциссы последней точки наблюденной кривой кажущ. сопротивления.
C Можно вести максимум 35 отсчетов. Это соответствует 25 точкам 
C трансформанты сопротивления, используемой при расчетах.
C  6. "Верно ?  Да=0". Если Вы отвечаете на этот вопрос отрицательно,
C т.е. вводите любое ненулевое число, то пограмма повторяет вопрос 5.
C После того, как вы ответили на перечисленные выше вопросы, программа
C выдает на печать вычисленные значения параметров первого слоя и 
C удельное сопротивление следующего слоя. Затем надо сделать следующий
C выбор: 
C   1) "Продолжить". В этом случае программа продолжается и вычисляет
C параметры второго слоя. 
C  2) "Выбрать глубину". Программа требует, чтобы вы задали глубину 
C границы слоя; используя это значение, она заново вычисляет параметры
C слоя. Затем программа продолжается и заново вычисляет параметры
C следующего слоя.
C 3) "Выбрать следующее удельное сопротивление". Это позволяет задать 
C удельное сопротивление следуюего слоя; программа работает так же,
C как в пункте 2)
C 4) "Выбрать глубину и следующее удельное сопротивление". Это дает
C возможность задать одновременно глубину залегания нижней границы 
C слоя и удельное сопротивление следующего слоя.
C Такой выбор делается после вычисления параметров каждого слоя.
C Пункты 2) и 4) не могут быть применены к первому слою, т.к. его 
C удельное сопротивление закреплено.
C После того, как программа исчерпала кривую ВЭЗ, полученные модельные
C параметры выдаются на печать вмсесте со средней квадратической
C относительной погрешностью и максимальной относительной погрешностью 
C кривой ВЭЗ, расситанной для полученной модели.
C  ====================================================================
C
      DIMENSION A(27), T(25), D(13), R(13)
C ********** INTODUCTION OF INFORMATION **************
      F=EXP(ALOG(10.)/8.)
1     PRINT 151
      READ(3,150) P
      PRINT 153
      READ(3,150) M
      IF (M) 8,2,8
2     PRINT 154
      READ(3,150) XA
      PRINT 155
      READ(3,150) JX
      JZ=JX-10
      PRINT 156, JX
      READ(3,150) A(1)
      R(1) = A(1)
      DO 4 J=2,17
4     A(J)=A(1)
      DO 5 J=18,26
5     READ(3,150) A(J)
      DO 7 K=1,JZ
      READ(3,150) A(27)
      B= .032*A(1) + .0022*A(3)+ .0044*A(5) + .0073*A)7) + .0136*A(9)
      B=B+ .0233*A(11) + .0425*A(13) + .0735*A(15) + .1309*A(17)
      B=B+ .2152*A(19) + .3224*A(21) + .2589*A(23) + .1099*A(25)
      T(K) = B + .0119*A(27)
      DO 6 J=1,26
6     A(J) = A(J+1)
7     CONTINUE
      PRINT 157
      READ(3,150) M
      IF(M) 3,8,3
8     D(1)=0.0
      DO 9 I=2,13
9     D(I)=R(I)=0.0
      X=1./(2.16*XA)
      DO 12 J=1,JZ
      A(J)=X
12    X=X/F
150   FORMAT (FF)
151   FORMAT('GIVE RELATIVE ERROR MARGIN')
153   FORMAT('NEW FIELD DATA? <YES=0>')
154   FORMAT('GIVE NUMBER OF SAMPLES')
155   FORMAT('GIVE',I3,'SAMPLE VALUES')  
157   FORMAT('CORRECT ? <YES=0>')
      I=0
      JS=J=1
      MM=1
20    I=I+1
      JP=JS
      JS=J
      JD=JS
      SW=SX=SY=SP=SQ=FQ=0.0
      DO 75 J=JS,JZ
      L=J+1-JD
C****************************************************************
C  COMPUTATION AND TESTING OF THE REDUCED RESISTIVITY TRANSFORM
C  AND OF THE MODIFIED KERNEL FUNCTION
C****************************************************************
      TR=T(J)
      TB=T(J)*(1.+P)
      TA=T(J)/(1.+P)
      IF(1-I) 31,36,36           ! ??????????????????
31    KW=I-1
      DO 32  K=1,KW
      TH=TANH(D(K)*A(J))
      TR=(TR-TH*R(K))/(1.-TR*TH/R(K))
      TA=(TA-TH*R(K))/(1.-TA*TH/R(K))
      TB=(TB-TH*R(K))/(1.-TB*TH/R(K))
32    CONTINUE 
      IF(TA) 38,38,35  
35    IF(TB) 38,38,36      
36    IF((TA-R(I))/(TB-R(I))) 38,38,39       
      JD=J+1
      GOTO 75
39    IF(J-JD) 40,40,41
      TX=TR
      G= ALOG(ABS((TR-R(I))/(TR+R(I))))
      GA=ALOG(ABS((TA-R(I))/(TA+R(I))))
      GB=ALOG(ABS((TB-R(I))/(TB+R(I))))
      IF(GB-GA) 42,43,43
42    BC=GA
      GA=GB
      GB=BC
43    IF(MM-2) 45,50,60
C ***** COMPUTATION FOR FREE CHOICE OF THE LAYER PARAMETERS *****
45    W=1./((GB-GA)*(GB-GA))            
      SW=SW+W
      SX=SX*W*A(J)
      SY=SY*W*G
      SP=SP+W*A(J)*G
      SQ=SQ+W*A(J)*A(J)
      FA=GA
      FB=GB
      FR=G
      FF=(FA+FB)/2.
      IF(2-L) 47,47,70
47    DI=-0.5*(SW+SP-SX*SY)/(SW*SQ-SX*SX) 
      RK=EXP((SY+2.*D(I)*SX)/SW)
      FF=ALOG(ABS(RK))-2.*D(I)*A(J)
      GOTO 70
C **** COMPUTATION FOR PRESCRIBED VALUE OF THE DEPTH ******
50    IF(2-L) 51,51,74      
51    BA=0.5/TANH(D(I)*(A(J-1)-A(J)))      
      BB=BA*(TQ-TR)
      FR=BB+SQRT(BB*BB+TQ*TR)
      BB=BA*(TQ-TB)
      RB=BB+SQRT(BB*BB+TQ*TB)
      BB=BA*(TQ-TA)
      RA=BB+SQRT(BB*BB+TQ*TA)
      IF(RB-RA) 53,53,54
53    BB=RB
      RB=RA
      RA=BB
54    FB=FR+1.4*(RB-FR)
      FA=FR-1.4*(FR-RA)
      FQ=EXP(2.*A(J)*D(I))*(TR-FR)/(TR+FR)
      GOTO 68
60    IF(MM-3) 139,61,62
C **** COMPUTATION FOR PRESCRIBED VALUE OF THE NEXT RESISTIVITY ******
61    FR=0.5*(RK-G)/A(J)             
      FA=0.5*(RK-GB)/A(J)
      FB=0.5*(RK-GA)/A(J)
      GOTO 68
C **** COMPUTATION FOR PRESCRIBED VALUE OF THE DRPTH AND THE  
C      NEXT RESISTIVITY ******
62    BA=0.5/TANH(A(J)D(I))      
      BB=BA*(TR-R(I+1)) 
      FR=BB+SQRT(BB*BB+TR*R(I+1))
      BB=BA*(TA-R(I+1)) 
      FA=BB+SQRT(BB*BB+TA*R(I+1))
      BB=BA*(TB-R(I+1)) 
      FB=BB+SQRT(BB*BB+TB*R(I+1))
      IF (FB-FA) 64,68,68
64    BB=FB
      FB=FA
      FA=BB
68    W=1./((FB-FA)*(FB-FA))
      SW=SW+W
      SY=SY+W*FR
      SQ=SQ+W*FQ
      FF=SY/SW
70    IF (FF-FB) 73,74,80
73    IF (FA-FF) 74,74,80      
74    TQ=TR
75    CONTINUE
C ****** ASSESSMENT OF THE VALUES OF THE LAYER PARAMETERS *****       
      IF (JD-JZ) 77,78,139 
77    IF (MM-2) 83,95,95       
78    IF (MM-2) 111,111,95
80    JF=J-1      
      SW=SW-W
      SY=SY-W*FR
      SQ=SQ-W*FQ
      IF (MM-1) 82,82,90
82    SX=SX-W*A(J) 
      SP=SP-W*A(J)*G
      SQ=SQ-W*A(J)*A(J)
      D(I)=-0.5*(SW*SP-SX*SY)/(SW*SQ-SX*SX) 
      RK=EXP((SY+2.*D(I)*SX)/SW)
83    IF (1.-RK) 84,84,86
84    RK=.98
      D(I)=.5*(SW*ALOG(RK)-SY)/SX
86    IF (TQ-TX) 87,88,88
87    RK=-RK        
88    R(I+1)=R(I)*(1.+RK)/(1.-RK)      
      GOTO 105
90    FF=SY/SW
C **** PROVISION FOR BRANCHING FACILITIES ****
95    IF (MM-3) 96,103,96
96    R(I)=FF 
      IF (MM-3) 100,103,105
100   RK=SQ/SW
      IF (1.-RK) 101,101,102
101   RK=.98
      GOTO 88
102   IF (1.+RK) 104,104,88
104   RK=-.98
      GOTO 88
103   D(I)=FF
105   PRINT 161,I
      PRINT 162
      BA=1./A(JD)
      BB=1./A(JF)
      PRINT 163, BA,BB,D(I),R(I),R(I+1)
161   FORMAT('MODEL DATA LAYER',I4)
162   FORMAT('ABSCISSA RANGE    THICKNESS RESIST.      NEXT RESIST.')
163   FORMAT(F7.2,' TO ',F8.2,3F11.2)
      IF (D(I)) 92,92,91
91    IF (MM-1) 106,106,108
92    PRINT  164, TX, TQ
      IF (MM-1) 93,106,94
93    I=I-1
      J=J5
      JS=JP
94    PRINT 185, I
164   FORMAT('FIRST AND  LAST TRANSFORM VALUE',F10.2,' AND ',F10.2)
185   FORMAT('CHANGE PREVIOUS CHOICE FOR LAYER',I4)
106   PRINT 165
      PRINT 166
165   FORMAT('CONTINUE (1), CHOICE DEPTH (2), CHOOSE NEXT RESISTIVITY')
166   FORMAT('(3), OR CHOOSE DEPTH AND NEXT RESISTIVITY (4)') 
      READ(3,150) MM
      IF(MM-1) 130,109,107
107   IF(MM-3) 118,116,118
108   MM=0
109   IF(J-JZ) 20,110,130
110   I=I+1
      JP=JS
      JS=J
111   PRINT 167
      PRINT 168
      PRINT 169
167   FORMAT('ONLY ONE SAMPLE LEFT') 
168   FORMAT('STOP (0), CHOOSE NEXT RESISTIVITY (3), OR CHOOSE') 
169   FORMAT('  DEPTH AND NEXT RESISTIVITY (4)')
      READ(3,150) MM
      IF(MM-3) 139,116,118
116   PRINT 170
170   FORMAT('GIVE NEXT RESISTIVITY')
      READ(3,150) R(I+1)
119   RK=ALOG(ABS((R(I+1)-R(I))/(R(I+1)+R(I)))) 
      GOTO 24
118   IF(I-1) 130,120,121
120   PRINT 190
190   FORMAT('ILLEGAL CHOICE')
      GOTO 106 
121   PRINT 172      
172   FORMAT('GIVE DEPTH BOUNDARU PLANE') 
      READ(3,150) DP
124   K=I-1       
      DR=DP
      DO 125 L=1,K
125   DR=DR-D(L)
      D(I)=DR
128   IF(MM-3) 24,24,116
C ****** PRESENTATION AND TESTING OF THE FINAL RESULTS ******
130   I=I+1
139   PRINT 174
      PRINT 175
174   FORMAT('FINAL SOLUTION')
175   FORMAT('     LAYER RESISTIVITY    THICKNESS')
176   FORMAT(I6,2F12.2)
      DO 131 K=1,I
131   PRINT 176, K,R(K),D(K)
      X=2.16*XA
      Q=BG=0.0
      DO 137 J=1,JZ
      B=R(I)
      IF(I-1) 136,136,135
135   DO 132 KW=2,I
      K=I+1-KW
      TH=TANH(D(K)/X)
132   B=(B+TH*R(K))/(1.+TH*B/R(K))
136   A(J)=S=(B-T(J))/T(J)      
      Q=Q+S*S
      IF(ABS(S)-BG) 134,134,133
133   BG=ABS(S)
      L=J
134   X=X*F
137   CONTINUE
      Q=SQRT(Q/FLOAT(JZ))
      PRINT 177,Q
      PRINT 178, A(L), L
177   FORMAT('R.M.S RELATIVE ERROR IS', F10.4)
178   FORMAT('MAXIMUM REL. ERROR IS ', F10.4, ' AT SAMPLE POINT ',I4)
      PRINT 180
      READ(3,150) M
      IF(M) 145, 141, 145
141   PRINT 181
180   FORMAT('COMPLETE OUTPRINT OF RESULTS WANTED? YES=0')
181   FORMAT('     ABSCISSA    TRANSFORM    REL.ERROR')
      X=2.16*XA
      DO 142 J=1,JZ
      PRINT 182,  X, T(J), A(J)
142   X=X*F
182   FORMAT(2F11.2 F11.4)
145   STOP
      END


