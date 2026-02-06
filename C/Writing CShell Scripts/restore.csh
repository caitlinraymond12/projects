#!/bin/csh



echo

set cp = /compat/linux/usr/bin/cp
set date = /compat/linux/usr/bin/date
set ls = /compat/linux/usr/bin/ls
set rm = /compat/linux/usr/bin/rm


set backup = "./backup"



set delete = 0
if("$argv[1]" =~ "*D*") then
    set delete = 1
endif
switch($argv[1])
    case "-c":
        set files = `ls backup`
        while($#files)
            rm ${backup}/${files[1]}
            shift files
        end
    breaksw


    case "*f*":
        while($#argv > 1) 
            if(-e ${backup}/$argv[2]) then 
                if( -f ${backup}/$argv[2]) then 
                    cp ${backup}/$argv[2] "./"
                    if(${delete}) then
                        rm ${backup}/$argv[2]
                    endif
                else
                    echo Can only restore regular files
                endif
            else 
                echo -n ${argv[2]}
                echo -n " "
                echo not in backup
            endif

    breaksw



    default:
        while($#argv > 0)
            if("${argv[1]}" != "-D") then 
                if( -e ${argv[1]}) then 
                    echo -n ${argv[1]}
                    echo -n " "
                    echo already exists in parent
                else
                    if( -f ${backup}/$argv[1]) then
                        cp ${backup}/$argv[1] "./"
                        if(${delete}) then
                            rm ${backup}/$argv[1]
                        endif
                    else
                        echo Can only restore regular files
                    endif
                endif
            endif
            shift argv
        end
    breaksw
endsw







echo 



exit 0



