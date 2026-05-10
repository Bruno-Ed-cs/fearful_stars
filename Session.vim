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
badd +73 src/dev_runner.cpp
badd +64 CMakeLists.txt
badd +43 term://~/projects/gamedev/fearful_stars//25587:/bin/bash
badd +178 src/main.cpp
badd +86 src/gameplay/components.hpp
badd +1 src/prod_runner.cpp
badd +8 ~/projects/gamedev/fearful_stars/src/main.hpp
badd +155 src/gameplay/player/player.cpp
badd +21 src/gameplay/projectile/projectile_manager.hpp
badd +51 src/gameplay/projectile/projectile_manager.cpp
badd +1 h\ path
badd +104 src/gameplay/player/player.hpp
badd +1 oil:///home/huevo/projects/gamedev/fearful_stars/
badd +1 man://std::vector(3)
badd +15 ~/projects/gamedev/fearful_stars/src/gameplay/projectile/projectile.hpp
badd +1 man://std::list(3)
badd +1304 include/raylib.h
badd +1 src/engine/container.hpp
badd +1 src/gameplay/projectile/plasma/plasma.cpp
badd +18 src/gameplay/projectile/plasma/plasma.hpp
badd +0 man://std::optional(3)
argglobal
%argdel
$argadd oil:///home/huevo/projects/gamedev/fearful_stars/
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/gameplay/projectile/plasma/plasma.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 94 + 87) / 174)
exe 'vert 2resize ' . ((&columns * 79 + 87) / 174)
argglobal
balt src/gameplay/projectile/projectile_manager.cpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
10
sil! normal! zo
let s:l = 2 - ((1 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 2
normal! 05|
wincmd w
argglobal
if bufexists(fnamemodify("src/gameplay/projectile/plasma/plasma.hpp", ":p")) | buffer src/gameplay/projectile/plasma/plasma.hpp | else | edit src/gameplay/projectile/plasma/plasma.hpp | endif
if &buftype ==# 'terminal'
  silent file src/gameplay/projectile/plasma/plasma.hpp
endif
balt src/gameplay/components.hpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
16
sil! normal! zo
let s:l = 18 - ((17 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 18
normal! 05|
wincmd w
exe 'vert 1resize ' . ((&columns * 94 + 87) / 174)
exe 'vert 2resize ' . ((&columns * 79 + 87) / 174)
tabnext
edit src/gameplay/components.hpp
argglobal
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
81
sil! normal! zo
91
sil! normal! zo
let s:l = 86 - ((20 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 86
normal! 031|
tabnext
argglobal
if bufexists(fnamemodify("term://~/projects/gamedev/fearful_stars//25587:/bin/bash", ":p")) | buffer term://~/projects/gamedev/fearful_stars//25587:/bin/bash | else | edit term://~/projects/gamedev/fearful_stars//25587:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/projects/gamedev/fearful_stars//25587:/bin/bash
endif
balt CMakeLists.txt
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 43 - ((42 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 43
normal! 0
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
