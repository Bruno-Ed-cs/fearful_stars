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
badd +23 src/gameplay/player/player.hpp
badd +12 imgui.ini
badd +72 src/gameplay/player/player.cpp
badd +12 ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/simple/simple.hpp
badd +1 ~/Projects/gamedev/fearful_stars/src/gameplay/projectile/projectile_template.txt
badd +1 src/gameplay/projectile/projectile_manager.cpp
badd +1 src/gameplay/player/player_manager.hpp
badd +17 src/gameplay/projectile/projectile_manager.hpp
badd +0 oil:///home/huevo/Projects/gamedev/fearful_stars/
badd +13 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/shooting_machine.hpp
badd +4 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/basic_shot.hpp
badd +45 ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/basic_shot.cpp
argglobal
%argdel
$argadd oil:///home/huevo/Projects/gamedev/fearful_stars/
edit ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/basic_shot.hpp
argglobal
balt ~/Projects/gamedev/fearful_stars/src/gameplay/player/primary_shots/basic_shot.cpp
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=10
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 4 - ((3 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 4
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
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
