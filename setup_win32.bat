@echo off
echo Checking directories ...


call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\cg-gt-rwd
copy .\src\drivers\human\cg-gt-rwd\skin.png .\runtime\drivers\human\cg-gt-rwd\skin.png
copy .\src\drivers\human\cg-gt-rwd\skin.rgb .\runtime\drivers\human\cg-gt-rwd\skin.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-1
copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtime\drivers\human\tracks\dirt-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-2
copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtime\drivers\human\tracks\dirt-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-3
copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtime\drivers\human\tracks\dirt-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-4
copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtime\drivers\human\tracks\dirt-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-5
copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtime\drivers\human\tracks\dirt-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-6
copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtime\drivers\human\tracks\dirt-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-1
copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtime\drivers\human\tracks\e-track-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-3
copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtime\drivers\human\tracks\e-track-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-4
copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtime\drivers\human\tracks\e-track-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-5
copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtime\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtime\drivers\human\tracks\e-track-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-6
copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtime\drivers\human\tracks\e-track-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-1
copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtime\drivers\human\tracks\mixed-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-2
copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtime\drivers\human\tracks\mixed-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\wheel-1
copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtime\drivers\human\tracks\wheel-1\car-mclaren-f1.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
copy .\src\drivers\human\car-buggy.xml .\runtime\drivers\human\car-buggy.xml
copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtime\drivers\human\car-cg-gt-rwd.xml
copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtime\drivers\human\car-cg-nascar-fwd.xml
copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtime\drivers\human\car-cg-nascar-rwd.xml
copy .\src\drivers\human\car-corvette.xml .\runtime\drivers\human\car-corvette.xml
copy .\src\drivers\human\car-lotus-gt1.xml .\runtime\drivers\human\car-lotus-gt1.xml
copy .\src\drivers\human\car-mclaren-f1.xml .\runtime\drivers\human\car-mclaren-f1.xml
copy .\src\drivers\human\car-p406.xml .\runtime\drivers\human\car-p406.xml
copy .\src\drivers\human\car-torcs.xml .\runtime\drivers\human\car-torcs.xml
copy .\src\drivers\human\car-viper-gts-r.xml .\runtime\drivers\human\car-viper-gts-r.xml
copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
