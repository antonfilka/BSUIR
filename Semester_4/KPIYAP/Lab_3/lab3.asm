.model	small
.stack	100h
.data
            
MaxArrayLength              equ 30            
            
ArrayLength                 db  ?
InputArrayLengthMsgStr      db  0Dh,'Input array length: $'
InputLowerBoundMsgStr       db  0Dh,'Input lower bound: $'  
InputHigherBoundMsgStr      db  0Dh,'Input higher bound: $'  
                                
ErrorInputMsgStr            db  0Dh,'Incorrect value!',0Ah, '$' 
ErrorInputHigherBoundMsgStr db  0Dh,'Higher bound should be geater than lower bound!', 0Ah, '$' 
ErrorInputArrayLengthMsgStr db  0Dh,'Array length should be geater than 0 and not grater than 30!', 0Ah, '$'
                                
InputMsgStr                 db  0Dh,'Input '    
CurrentEl                   db  2 dup(0)
InputMsgStrEnding           db  ' element (-127..127) : $'     
enterStr                    db  0Ah, 0Dh, '$'

Answer                      db  2 dup(0)
ResultMsgStr                db  0Dh, 'Result: $'
                                
Buffer                      db  ?
                                                              
MaxNumLen                   db  5  
Len                         db  ?                          ;Contains length of entered string
buff                        db  5 dup (0)              
                                
minus                       db  0  

Array                       db  MaxArrayLength dup (0) 
                                
LowerBound                  db  ?
HigherBound                 db  ?
                              
.code      
start:                            ;
mov	ax,@data                      ;
mov	ds,ax                         ;
                                  ;
xor	ax,ax                         ;
                                  ;
call input                        ;
call Do                           ;
call output                       ;
                                  ;
                                  ;
input proc                        ;
    call inputLowerBound          ;
    call inputHigherBound         ;
    call inputArrayLength         ;
    call inputArray               ;
                                  ;
    ret                           ;
endp     


inputLowerBound proc
    mov cx, 1                         
    inputLowerBoundLoop:
       call ShowInputLowerBoundMsg                    
       call inputElementBuff          
       
       test ah, ah
       jnz inputLowerBoundLoop 
       
       mov bl, Buffer 
       mov LowerBound, bl
    loop inputLowerBoundLoop                
    ret      
endp    

inputHigherBound proc                                    
    mov cx, 1                         
    inputHigherBoundLoop:
       call ShowInputHigherBoundMsg                    ;
       call inputElementBuff         
              
       test ah, ah
       jnz inputHigherBoundLoop 
       
       mov ah, LowerBound
       cmp Buffer,ah                                          
       jnl inputHigherBoundLoop_OK
       
       call ShowErrorInputHigherBoundMsgStr 
       jmp inputHigherBoundLoop
       
       inputHigherBoundLoop_OK:
       
       mov bl, Buffer 
       mov HigherBound, bl
    loop inputHigherBoundLoop
    ret      
endp     

inputArrayLength proc   
    mov cx, 1           
    inputArrayLengthLoop:
       call ShowInputArrayLengthMsg                    ;
       call inputElementBuff          
       
       test ah, ah
       jnz inputArrayLengthLoop 
       
       cmp Buffer, MaxArrayLength
       jg inputArrayLengthLoop_FAIL   
       
       cmp Buffer, 0
       jg inputArrayLengthLoop_OK   
       ;jmp inputArrayLengthLoop_FAIL
       
       inputArrayLengthLoop_FAIL:
       
       call ShowErrorInputArrayLengthMsgStr 
       jmp inputArrayLengthLoop
       
       inputArrayLengthLoop_OK:
       
       mov bl, Buffer 
       mov ArrayLength, bl                 
    loop inputArrayLengthLoop     
    ret      
endp 

inputArray proc
    xor di,di                     
                                               
    mov cl,ArrayLength            
    inputArrayLoop:
       call ShowInputMsg                    ;
       call inputElementBuff      
       
       test ah, ah
       jnz inputArrayLoop
       
       mov bl, Buffer 
       mov Array[di], bl
       inc di                     
    loop inputArrayLoop           
    ret      
endp  


resetBuffer proc
    mov Buffer, 0    
    ret
endp    

inputElementBuff proc                 ;
    push cx                       ;save cx
    inputElMain:                  ;
        call resetBuffer          ;
        
        mov ah,0Ah                ;Input command  
        lea dx, MaxNumLen         ;
        int 21h                   ;Input
                                  ;
        mov dl,10                 ;Ñèìâîë êîòîðûé íàäî âûâåñòè íà ýêðàí
        mov ah,2                  ;Ôóíêöèÿ DOS âûâîäà ñèìâîëà
        int 21h                   ;Ïðåðûâàíèå äëÿ âûïîëíåíèÿ ô-öèè
                                  ;
        cmp Len,0                 ;
        je errInputEl             ;If input is exmpty - exit
                                  ;
        mov minus,0               ;Reset minus
        xor bx,bx                 ;Reset bx
                                  ;
        mov bl,Len                ;
        lea si,Len                ;
                                  ;
        add si,bx                 ;
        mov bl,1                  ;
                                  ;
                                  ;
        xor cx,cx                 ;
        mov cl,Len                ;
        inputElLoop:              ;
            std                   ;Óñòàíîâêà ôëàãà íàïðàâëåíèÿ äâèæåíèÿ ïî ìàññèâó
            lodsb                 ;Ñ÷èòàòü áàéò ïî àäðåñó DS:SI â AL
                                  ;Òåïåðü â al íàõîäèòñÿ òåêóùèé ñèìâîë
            call checkSym         ;Ïðîâåðêà ÷èñëî ëè ýòî
                                  ;
            cmp ah,1              ;Åñëè ah ñîäåðæèò 1, òî çíà÷èò ñèìâîë íå ïðîøåë êîíòðîëü checkSym è â ïðîöåññå åå âûïîëíåíèÿ ñòàë 1
            je errInputEl         ;Îáðàáàòûâàåì äàííóþ ñèòóàöèþ
                                  ;
            cmp ah,2              ;Åñëè ah ïîñëå âûïîëíåíèÿ checkSym ñîäåðæèò 2, òî çíà÷èò áûë ââåäåí çíàê ìèíóñà, íåîáõîäèìà äàëüøåéíàÿ ïðîâåðêà 
            je nextSym            ;
                                  ;
            sub al,'0'            ;Åñëè ìû íàõîäèìñÿ íà ýòîì øàãó, òî â al ëåæèò ñèìâîë â äèàïàçîíå '0'..'9', îòíèìàåì '0' ÷òîáû ïîëó÷èòü åãî ÷èñëîâîå çíà÷åíèå
            mul bl                ;Óìíîæîåì òåêóùóþ öèôðó íà ðàçðÿä
                                  ;
            test ah,ah            ;Ïîáèòîâîå and ñ èçìåíåíèåì ÒÎËÜÊÎ ôëàãîâ, ðåçóëüòàò íå ñîõðàíÿåòñÿ
                                  ;Ïðîâåðêà çíà÷åíèÿ ðåãèñòðà íà ðàâåíñòâî íóëþ, Åñëè ðàâíî íóëþ -> Îøèáîê íå âûÿâëåíî
            jnz errInputEl        ;Åñëè íå íîëü - îøèáêà ââîäà
                                  ;
            add Buffer,al      ;Çàïèñûâàåì òåêóùóþ ÷àñòü ÷èñëà â ìàññèâ. Òèï 123 = 3 + 2*10 + 1*100
                                  ;
            jo errInputEl         ;Åñëè åñòü ïåðåïîíåíèå
            js errInputEl         ;Çíàê ðàâåí 1
                                  ;
            mov al,bl             ;Â al çàãðóæàåì bl
            mov bl,10             ;Â bl 10
            mul bl                ;Óìíîæàåì al íà 10, ïåðåõîä íà ñëåäóþùèé ðàçðÿä ÷èñëà
                                  ;
            test ah,ah            ;Ïîáèòîâîå and ñ ôëàãàìè îïÿòü
            jz ElNextCheck        ;Åñëè íóëü èëè ðàâíî
                                  ; 
                                  ;
            cmp ah,3              ;Åñëè ah !=3 îøèáêà ââîäà
            jne errInputEl        ;Ò.ê. 0..2 ìû ïðîâåðèëè, 10^3 â 16ññ = 3xx, òî 10^3 åùå äîïóñòèìà, à èç 10^4+ íåò
                                  ;
                                  ;
            ElNextCheck:          ;
                mov bl,al         ;
                jmp nextSym       ;
                                  ;
                                  ;
            errInputEl:           ;
                call ShowErrorInputMsg   ;Âûâîä ñîîáùåíèÿ îá îøèáêå ââîäà
                jmp exitInputEl          ;Ïîïûòêà ââåñòè ÷èñëî çàíîâî
                                  ;
            nextSym: 
            xor ah, ah            ;
        loop inputElLoop          ;
                                  ;
    cmp minus,0                   ;
    je exitInputEl                ;
    neg Buffer                    ;
                                  ;
    exitInputEl:                  ;
    pop cx                        ;Âîññòàíàâëèâàåì cx
    ret                           ;
endp 
        ;
                                  ;
checkSym proc                     ;
    cmp al,'-'                    ;Åñëè ýëåìåíò ðàâåí ìèíóñó, òî äåëàåì âûâîä, ÷òî ìû ïûòàåìñÿ ââåñòè îòðèöàòåëüíîå ÷èñëî
    je minusSym                   ;
                                  ;
    cmp al,'9'                    ;
    ja errCheckSym                ;Åñëè ñèìâîë áîëüøå 9 - îøèáêà ââîäà
                                  ;
    cmp al,'0'                    ;
    jb errCheckSym                ;Åñëè ñèìâîë ìåíüøå 0 - îøèáêà ââîäà
                                  ;
    jmp exitCheckGood             ;Åñëè ñèìâîë - öèôðà - ïåðåõîäèì â exitCheckGood, ãäå ñáðàñûâàåì ìåòêó îøèáêè
                                  ;
    minusSym:                     ;
        cmp si,offset Len         ;
        je exitWithMinus          ;
                                  ;
    errCheckSym:                  ;
        mov ah,1                  ;Incorrect symbol
        jmp exitCheckSym          ;
                                  ;
    exitWithMinus:                ;
        mov ah,2                  ;
        mov minus, 1              ;Óñòàíàâëèâàåì ìåòêó, ÷òî ÷èñëî îòðèöàòåëüíîå
        cmp Len, 1                ;
        je errCheckSym            ;Åñëè ÷èñëî ñîñòîèò òîëüêî èç ìèíóñà ëèáî áûëè ââåäåíû 2+ ìèíóñà - îøèáêà ââîäà!
                                  ;
        jmp exitCheckSym          ;
                                  ;
    exitCheckGood:                ;
        xor ah,ah                 ;Ah = 0 
                                  ;
    exitCheckSym:                 ;
        ret                       ;
endp                              ;
                                  ;
ShowErrorInputMsg proc                   ;Âûâîä ñîîáùåíèÿ îá îøèáêå âûâîäà
    lea dx, ErrorInputMsgStr      ;
    mov ah, 09h                   ;
    int 21h                       ;
    ret                           ;
endp                              ;
      

ShowInputArrayLengthMsg proc
    push ax
    push dx
      
    mov ah,09h                      
    lea dx, InputArrayLengthMsgStr           
    int 21h  
    
    pop ax
    pop dx 
     
    ret
endp       
         
ShowInputLowerBoundMsg proc
    push ax
    push dx
      
    mov ah,09h                      
    lea dx, InputLowerBoundMsgStr           
    int 21h  
    
    pop ax
    pop dx 
     
    ret
endp    

ShowInputHigherBoundMsg proc
    push ax
    push dx
      
    mov ah,09h                      
    lea dx, InputHigherBoundMsgStr           
    int 21h  
    
    pop ax
    pop dx 
     
    ret
endp  
                                  ;
ShowInputMsg proc                     ;
    mov ax,di                     ;di contains num
              
    mov ax, di         
    mov bl, 10
    div bl          
              
    push di
        
    xor di, di    
    inc di
    mov CurrentEl[di], ah
    add CurrentEl[di], '0'
    
    test al, al 
    jz lessThanTen
    
    dec di
    mov CurrentEl[di], al                      
    add CurrentEl[di], '0'           
           
    lessThanTen:                      ;
                                  ;
    mov ah,09h                    ;output command
    lea dx, InputMsgStr           ;show input msg to user
    int 21h   
    
    pop di
                        ;
    ret                           ;
endp    

ShowErrorInputHigherBoundMsgStr proc
    push ax
    push dx
      
    mov ah,09h                      
    lea dx, ErrorInputHigherBoundMsgStr           
    int 21h  
    
    pop ax
    pop dx 
     
    ret
endp       

ShowErrorInputArrayLengthMsgStr proc
    push ax
    push dx
      
    mov ah,09h                      
    lea dx, ErrorInputArrayLengthMsgStr           
    int 21h  
    
    pop ax
    pop dx 
     
    ret
endp

                                  ;
CheckMatch proc                   ;Ïðîöåäóðà ñðàâíåíèÿ
    mov ah, LowerBound                   ;Çàãðóæàåì â ah ëåâóþ ãðàíèöó äèàïàçîíà
    cmp Array[di],ah              ;Ñðàâíèâàåì                                         
    jl notMatch                   ;Åñëè ìîæíî ñäåëàòü âûâîä, ÷òî ýëåìåíò äèàïàçîíó íå ïðèíàäëåæèò - âûõîäèì èç ïðîöåäóðû
                                  ;
    mov ah, HigherBound           ;Àíàëîãè÷íî äëÿ ïðàâîé ãðàíèöû ìàññèâà
    cmp Array[di],ah              ;
    jg notMatch                   ;
                                  ;
    inc bx                        ;bx ñîäåðæèò ñêîëüêî ýëåìåíòîâ                   ;
                                  ;
    notMatch:                     ;
    ret                           ;
endp                              ;
                                  ;
Do proc                           ;
    xor bx, bx                    ;Îáíóëÿåì bx, ò.ê â bx áóäåò õðàíèòüñÿ îòâåò
    mov cl,ArrayLength            ;Çàãðóæàåì â cx äëèíó ìàññèâà, ÷òîáû ÷åðåç loop ïðîéòèñü ïî êàæäîìó ýëåìåíòó
    xor di, di                    ;Îáíóëÿåì di, ò.ê. ïðîõîä áóäåì íà÷èíàòü â íóëåâîãî ýëåìåíòà
    DoLoop:                       ;
        call CheckMatch           ;Âûçîâ ôóíêöèè ïðîâåðêè
        inc  di                   ;Óâåëè÷èâàåì di ÷òîáû ïåðåéòè ê íîâîìó ýëåìåíòó
    loop DoLoop                   ;
    ret                           ;
endp                              ;
                                  ;
output proc                       ;
    lea dx, ResultMsgStr          ;                                                        
    mov ah, 09h
    int 21h
            
    mov ax, bx         
    mov al, bl
    mov bl, 10
    div bl
                   
    xor di, di    
    inc di
    mov Answer[di], ah
    add Answer[di], '0'
    
    test al, al 
    jz lessThanTen1
    
    dec di
    mov Answer[di], al                      
    add Answer[di], '0'           
           
    lessThanTen1:                      ;
    
    lea dx, Answer
    mov ah, 09h 
    int 21h      
    
    lea dx, enterStr
    mov ah, 09h 
    int 21h  
        
    xor ax, ax                              ;
    mov	ah,4ch                    ;Âûõîäèì èç ïðîãðàììû
    int	21h                       ;
    ret                           ;
endp                              ;
                                  ;
end	start                         ;