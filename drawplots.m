% Antalet v�rden som ska plottas
N = 600;

%L�gger till array:er f�r att spara v�rdena som skickas fr�n atmel
firststyrvarde =zeros(1,N);
secfelvarde =zeros(1,N);
thirdborvarde =zeros(1,N);
fourthcurrentvalue = zeros(1,N);
tid = zeros(1,N);
    
% For-loop d�r vi tar in alla v�rden och plottar dom.
for i=1:N
    
    flushinput(s);
    
    tid(i) =i;
    %L�ser in v�rden
    tempfirststyrvarde = fscanf(s)
    tempsecfelvarde = fscanf(s)
    tempthirdborvarde = fscanf(s)
    tempfourthcurrentvalue = fscanf(s)
    
    %G�r om dom fr�n string till double s� att vi kan plotta dom
    firststyrvarde(i) =str2double(tempfirststyrvarde);
    secfelvarde(i) =str2double(tempsecfelvarde);
    thirdborvarde(i) =str2double(tempthirdborvarde);
    fourthcurrentvalue(i) = str2double(tempfourthcurrentvalue);
    
    %plottnigen
    plot(tid,firststyrvarde,'k--',tid,secfelvarde,'g--',tid,thirdborvarde,'b--',tid,fourthcurrentvalue,'r--');
    title('f�rh�llandet fr�n objekt till sensorn');
    xlabel('Sampling');
    ylabel('avst�nd fr�n sensor[cm]');
    legend('styrv�rde','felv�rde','B�rv�rde','pingisbollens avst�nd');
    grid on
    drawnow;
    
end    
disp('done');
fclose(s);
delete(s);