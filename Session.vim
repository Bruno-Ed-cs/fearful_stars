let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
doautoall SessionLoadPre
silent only
silent tabonly
cd ~/projects/gamedev/fearful_stars
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess+=aoO
badd +107 src/main.cpp
badd +1 src/dev_runner.cpp
badd +1 src/prod_runner.cpp
badd +51 CMakeLists.txt
badd +1311 term://~/projects/gamedev/fearful_stars//6219:/bin/bash
badd +4 src/main.hpp
badd +16 src/engine/component.hpp
badd +33 src/engine/container.hpp
badd +188 src/gameplay/components.hpp
badd +43 src/systems.hpp
badd +80 src/gameplay/player/player.hpp
badd +19 src/engine/entity.hpp
badd +9 src/gameplay/player/player.cpp
badd +49 ~/projects/gamedev/fearful_stars/src/gameplay/ui/interfaces/gameplay_ui.hpp
badd +6 src/gameplay/player/player_manager.cpp
badd +12 src/update_loop.hpp
badd +9 src/draw_loop.hpp
badd +18 src/gameplay/player/player_manager.hpp
badd +12 src/globals.hpp
badd +3 src/engine/render_man.cpp
badd +9 src/gameplay/levels/levels.cpp
badd +7 src/gameplay/enemy/broken_ship/broken_ship.cpp
badd +8 src/gameplay/enemy/anemonae/anemonae.cpp
badd +8 src/gameplay/enemy/minion/minion.cpp
badd +8 src/gameplay/enemy/basic/basic_enemy.cpp
badd +8 src/gameplay/enemy/eye/crystal_eye.cpp
badd +7 src/gameplay/projectile/projectile_manager.cpp
badd +8 src/gameplay/enemy/chaser/chaser.cpp
badd +7 src/gameplay/projectile/basic/basic_projectile.cpp
badd +9 src/gameplay/enemy/vagant/vagant.cpp
badd +0 oil:///home/huevo/projects/gamedev/fearful_stars/
argglobal
%argdel
$argadd oil:///home/huevo/projects/gamedev/fearful_stars/
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/gameplay/components.hpp
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt src/engine/container.hpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
177
sil! normal! zo
let s:l = 189 - ((31 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 189
normal! 0
tabnext
argglobal
if bufexists(fnamemodify("term://~/projects/gamedev/fearful_stars//6219:/bin/bash", ":p")) | buffer term://~/projects/gamedev/fearful_stars//6219:/bin/bash | else | edit term://~/projects/gamedev/fearful_stars//6219:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/projects/gamedev/fearful_stars//6219:/bin/bash
endif
balt src/prod_runner.cpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 224 - ((41 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 224
normal! 04|
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
