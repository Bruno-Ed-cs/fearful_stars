let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Projects/gamedev/fearful_stars
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +38 src/gameplay/player/player.hpp
badd +6 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/shooting_machine.hpp
badd +15 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/plasma_shot.hpp
badd +40 ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/plasma/plasma.hpp
badd +15 ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/missile/missile_proj.hpp
badd +4 ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/missile/missile_proj.cpp
badd +1 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/plasma_shot.cpp
badd +58 src/gameplay/player/player_manager.cpp
badd +5 ~/Projects/gamedev/fearful_stars/src/gameplay/player/secondary_shots/secondary_machine.hpp
badd +5 ~/Projects/gamedev/fearful_stars/src/gameplay/player/aux_powers/aux_machine.hpp
badd +15 src/engine/music_man.hpp
badd +131 ~/Projects/gamedev/fearful_stars/src/engine/music_man.cpp
badd +7 ~/Projects/gamedev/fearful_stars/src/gameplay/components/position.hpp
badd +17 ~/Projects/gamedev/fearful_stars/src/gameplay/components/direction.hpp
badd +123 ~/Projects/gamedev/fearful_stars/src/engine/background_man.cpp
argglobal
%argdel
$argadd oil:///home/huevo/Projects/gamedev/fearful_stars/
edit ~/Projects/gamedev/fearful_stars/src/engine/background_man.cpp
argglobal
balt ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/missile/missile_proj.hpp
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=10
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 123 - ((38 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 123
normal! 0
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
