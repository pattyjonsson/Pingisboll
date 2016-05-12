%ansluter sig till arduino-kortet
s = serial('COM13', 'BAUDRATE', 115200)

%�ppnar porten
set(s, 'Terminator', 10);
fopen(s);

%Pausar i 4 sekunder och flushar in och utg�ng 
%s� att inga gamla v�rdet �r kvar
pause(4);
flushinput(s);
flushoutput(s);

%H�r skickar vi v�rt f�rsta v�rde t
fwrite(s, uint8(5))

%PID-variablerna. Vi dividerar dom med 100 i atmel f�r att f� ut de riktiga
%v�rdena
temp=0;
kp = 090; 
Td = 033;
Ti = 160;
borvarde = 25;


temp=fscanf(s);
disp(temp);


%Skickar KP-v�rdet och f�r tillbaka en verifiering
fwrite(s, uint8(kp))
temp=fscanf(s);
disp('Kp=');
disp(temp);

%Skickar TI v�rdet och f�r tillbaka en verifiering
fwrite(s, uint8(Ti))
temp=fscanf(s);
disp('Ti=');
disp(temp);

%Skickar Td v�rdet och f�r tillbaka en verifiering
fwrite(s, uint8(Td))
temp=fscanf(s);
disp('Td=');
disp(temp)

% H�r skickar vi b�rv�rdet och f�r tillbaka en verifiering
fwrite(s, uint8(borvarde))  
temp=fscanf(s);
disp('Bv=');
disp(temp);

