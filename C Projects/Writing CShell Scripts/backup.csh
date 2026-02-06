#!/bin/csh



echo

set cp = /compat/linux/usr/bin/cp
set date = /compat/linux/usr/bin/date
set ls = /compat/linux/usr/bin/ls
set rm = /compat/linux/usr/bin/rm


set backup = "./backup"


switch($argv[1])
    case "-f":
        while($#argv > 1)
            if(-f ${argv[2]}) then 
                cp $argv[2] backup
            else
                echo Can only backup regular files
            endif
            shift argv
        end
    breaksw

    case "-s":
    while($#argv > 1)
            if( -e ${backup}/$argv[2]) then
                echo -n ${argv[2]} 
                echo -n " "
                date -r ${backup}/${argv[2]}
            else
                echo File ${argv[2]} does not exist in backup directory.
            endif
            shift argv

        end
    breaksw

    case "-l":
        set files = `ls backup`
        while($#files)
            echo -n ${files[1]}
            echo -n " "
            date -r ${backup}/${files[1]}
            shift files

        end
    breaksw


    default:
        while($#argv > 0)
            if( -e ${backup}/$argv[1]) then 
                echo -n ${argv[1]} 
                echo -n " "
                date -r ${argv[1]}  
            else
                if(-f ${argv[1]}) then
                    cp $argv[1] backup #why doesn't backup need {} or anyting
                else
                    echo Can only backup regular files
                endif
            endif
            shift argv
        end
    breaksw
endsw


echo 



exit 0



