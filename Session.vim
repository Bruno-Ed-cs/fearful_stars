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
badd +118 src/gameplay/player/player.hpp
badd +23 ~/projects/gamedev/fearful_stars/.clangd
badd +4 src/gameplay/player/player_manager.cpp
badd +139 src/main.cpp
badd +56 ~/projects/gamedev/fearful_stars/src/gameplay/enemy/broken_ship/broken_ship.cpp
badd +470 term://~/projects/gamedev/fearful_stars//20946:/bin/bash
badd +171 src/engine/container.hpp
badd +52 build.zig
badd +15 src/engine/render_man.cpp
badd +16 src/systems.cpp
badd +1 src/gameplay/ui/ui_man.hpp
badd +1 src/gameplay/ui/ui_layer.hpp
badd +29 src/gameplay/ui/interfaces/gameplay_ui.hpp
badd +5 src/gameplay/components.hpp
badd +1 src/gameplay/ui/ui_man.cpp
badd +4 src/engine/component.hpp
badd +74 ~/projects/gamedev/fearful_stars/src/engine/entity.hpp
badd +55 src/gameplay/ui/interfaces/pause_ui.hpp
badd +4 ~/projects/gamedev/fearful_stars/src/deps.hpp
argglobal
%argdel
$argadd .
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/engine/container.hpp
argglobal
balt src/gameplay/ui/interfaces/gameplay_ui.hpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
18
sil! normal! zo
32
sil! normal! zo
36
sil! normal! zo
48
sil! normal! zo
51
sil! normal! zo
62
sil! normal! zo
64
sil! normal! zo
92
sil! normal! zo
94
sil! normal! zo
144
sil! normal! zo
148
sil! normal! zo
162
sil! normal! zo
164
sil! normal! zo
let s:l = 178 - ((34 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 178
normal! 039|
tabnext
argglobal
if bufexists(fnamemodify("term://~/projects/gamedev/fearful_stars//20946:/bin/bash", ":p")) | buffer term://~/projects/gamedev/fearful_stars//20946:/bin/bash | else | edit term://~/projects/gamedev/fearful_stars//20946:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/projects/gamedev/fearful_stars//20946:/bin/bash
endif
balt ~/projects/gamedev/fearful_stars/src/gameplay/enemy/broken_ship/broken_ship.cpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 5560 - ((42 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5560
normal! 02|
tabnext 1
set stal=1
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
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
