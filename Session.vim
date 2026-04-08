let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/projects/gamedev/fearful_stars
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +48 build.zig.zon
badd +62 build.zig
badd +84 src/gameplay/player/player.hpp
badd +1202 term://~/projects/gamedev/fearful_stars//27133:/bin/bash
badd +150 src/main.cpp
badd +269 ~/.zvm/0.15.2/lib/libcxx/include/__memory/unique_ptr.h
badd +3 src/engine/asset_man.hpp
badd +7 src/deps.hpp
badd +1858 ~/.zvm/0.15.2/lib/libcxx/include/algorithm
badd +26 ~/.zvm/0.15.2/lib/libcxx/include/__algorithm/inplace_merge.h
badd +15 src/draw_loop.hpp
badd +224 term://~/projects/gamedev/fearful_stars//2056:/bin/bash
argglobal
%argdel
$argadd .
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/main.cpp
argglobal
balt src/gameplay/player/player.hpp
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
69
sil! normal! zo
116
sil! normal! zo
let s:l = 150 - ((29 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 150
normal! 0
tabnext
argglobal
if bufexists(fnamemodify("term://~/projects/gamedev/fearful_stars//27133:/bin/bash", ":p")) | buffer term://~/projects/gamedev/fearful_stars//27133:/bin/bash | else | edit term://~/projects/gamedev/fearful_stars//27133:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/projects/gamedev/fearful_stars//27133:/bin/bash
endif
balt build.zig
setlocal foldmethod=indent
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 1202 - ((41 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1202
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
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
