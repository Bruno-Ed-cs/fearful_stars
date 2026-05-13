let SessionLoad = 1
let s:cpo_save=&cpo
set cpo&vim
cnoremap <silent> <Plug>(TelescopeFuzzyCommandSearch) e "lua require('telescope.builtin').command_history { default_text = [=[" . escape(getcmdline(), '"') . "]=] }"
inoremap <silent> <C-Space> 
inoremap <C-W> u
inoremap <C-U> u
nnoremap <silent> 	t <Cmd>tab term
nnoremap <silent> 	d :tabclose
nnoremap <silent> 	n :tabnew
nnoremap  <Cmd>nohlsearch|diffupdate|normal! 
xnoremap <silent> a :lua MiniSurround.add("visual")
nmap  d
tnoremap  
nnoremap <silent>  :tabprevious
nnoremap <silent>  :tabnext
nnoremap <silent>  dg :diffget
nnoremap <silent>  dp :diffput
nnoremap  cl :Telescope colorscheme
nnoremap <silent>  m :make
nnoremap <silent>  cc :cclose
nnoremap <silent>  co :copen
nnoremap <silent>  cp :cprevious
nnoremap <silent>  cn :cnext
nnoremap  sG :LiveGrepGitRoot
nnoremap  xx <Cmd>Oil
nnoremap <silent>  ; A;j0
omap <silent> % <Plug>(MatchitOperationForward)
xmap <silent> % <Plug>(MatchitVisualForward)
nmap <silent> % <Plug>(MatchitNormalForward)
nnoremap & :&&
xnoremap <silent> <expr> @ mode() ==# 'V' ? ':normal! @'.getcharstr().'' : '@'
xnoremap <silent> <expr> Q mode() ==# 'V' ? ':normal! @=reg_recorded()' : 'Q'
nnoremap Y y$
omap <silent> [% <Plug>(MatchitOperationMultiBackward)
xmap <silent> [% <Plug>(MatchitVisualMultiBackward)
nmap <silent> [% <Plug>(MatchitNormalMultiBackward)
omap <silent> ]% <Plug>(MatchitOperationMultiForward)
xmap <silent> ]% <Plug>(MatchitVisualMultiForward)
nmap <silent> ]% <Plug>(MatchitNormalMultiForward)
xmap a% <Plug>(MatchitVisualTextObject)
omap <silent> g% <Plug>(MatchitOperationBackward)
xmap <silent> g% <Plug>(MatchitVisualBackward)
nmap <silent> g% <Plug>(MatchitNormalBackward)
tnoremap <silent> <Plug>(fzf-normal) 
tnoremap <silent> <Plug>(fzf-insert) i
nnoremap <silent> <Plug>(fzf-normal) <Nop>
nnoremap <silent> <Plug>(fzf-insert) i
xmap <silent> <Plug>(MatchitVisualTextObject) <Plug>(MatchitVisualMultiBackward)o<Plug>(MatchitVisualMultiForward)
onoremap <silent> <Plug>(MatchitOperationMultiForward) :call matchit#MultiMatch("W",  "o")
onoremap <silent> <Plug>(MatchitOperationMultiBackward) :call matchit#MultiMatch("bW", "o")
xnoremap <silent> <Plug>(MatchitVisualMultiForward) :call matchit#MultiMatch("W",  "n")m'gv``
xnoremap <silent> <Plug>(MatchitVisualMultiBackward) :call matchit#MultiMatch("bW", "n")m'gv``
nnoremap <silent> <Plug>(MatchitNormalMultiForward) :call matchit#MultiMatch("W",  "n")
nnoremap <silent> <Plug>(MatchitNormalMultiBackward) :call matchit#MultiMatch("bW", "n")
onoremap <silent> <Plug>(MatchitOperationBackward) :call matchit#Match_wrapper('',0,'o')
onoremap <silent> <Plug>(MatchitOperationForward) :call matchit#Match_wrapper('',1,'o')
xnoremap <silent> <Plug>(MatchitVisualBackward) :call matchit#Match_wrapper('',0,'v')m'gv``
xnoremap <silent> <Plug>(MatchitVisualForward) :call matchit#Match_wrapper('',1,'v'):if col("''") != col("$") | exe ":normal! m'" | endifgv``
nnoremap <silent> <Plug>(MatchitNormalBackward) :call matchit#Match_wrapper('',0,'n')
nnoremap <silent> <Plug>(MatchitNormalForward) :call matchit#Match_wrapper('',1,'n')
nnoremap <Plug>PlenaryTestFile :lua require('plenary.test_harness').test_file(vim.fn.expand("%:p"))
xnoremap <silent> <C-S>a :lua MiniSurround.add("visual")
nnoremap <silent> <C-[> :tabprevious
nnoremap <silent> <C-]> :tabnext
nnoremap <silent> <S-F7> <Cmd>CompilerToggleResults
nnoremap <silent> <S-F6> <Cmd>CompilerStop<Cmd>CompilerRedo
nnoremap <silent> <F6> <Cmd>CompilerOpen
nmap <C-W><C-D> d
nnoremap <C-L> <Cmd>nohlsearch|diffupdate|normal! 
inoremap  u
inoremap  u
let &cpo=s:cpo_save
unlet s:cpo_save
set autocomplete
set autocompletedelay=300
set clipboard=unnamedplus
set completeopt=fuzzy,nearest,popup,menu,menuone,noselect,noinsert
set confirm
set expandtab
set grepformat=%f:%l:%c:%m
set grepprg=rg\ --vimgrep\ -uu\ 
set helplang=en
set ignorecase
set makeprg=make\ -j\ -C\ build
set pumblend=50
set pumborder=solid
set pumheight=12
set pummaxwidth=40
set pumwidth=50
set runtimepath=~/.config/nvim,~/.config/kdedefaults/nvim,/etc/xdg/nvim,~/.local/share/nvim/site,~/.local/share/nvim/site/pack/core/opt/focus.nvim,~/.local/share/nvim/site/pack/core/opt/tabby.nvim,~/.local/share/nvim/site/pack/core/opt/lsp_signature.nvim,~/.local/share/nvim/site/pack/core/opt/oil.nvim,~/.local/share/nvim/site/pack/core/opt/nvim-treesitter,~/.local/share/nvim/site/pack/core/opt/telescope-fzf-native.nvim,~/.local/share/nvim/site/pack/core/opt/ripgrep,~/.local/share/nvim/site/pack/core/opt/plenary.nvim,~/.local/share/nvim/site/pack/core/opt/nightfox.nvim,~/.local/share/nvim/site/pack/core/opt/which-key.nvim,~/.local/share/nvim/site/pack/core/opt/telescope.nvim,~/.local/share/nvim/site/pack/core/opt/lspkind.nvim,~/.local/share/nvim/site/pack/core/opt/mason-lspconfig.nvim,~/.local/share/nvim/site/pack/core/opt/mason.nvim,~/.local/share/nvim/site/pack/core/opt/nvim-lspconfig,~/.local/share/nvim/site/pack/core/opt/mini.nvim,~/.local/share/flatpak/exports/share/nvim/site,/var/lib/flatpak/exports/share/nvim/site,/usr/local/share/nvim/site,/usr/share/nvim/site,/usr/share/nvim/runtime,/usr/share/nvim/runtime/pack/dist/opt/matchit,/usr/share/nvim/runtime/pack/dist/opt/nvim.difftool,/usr/share/nvim/runtime/pack/dist/opt/nvim.undotree,/usr/lib/nvim,~/.local/share/nvim/site/pack/core/opt/mason-lspconfig.nvim/after,/usr/share/nvim/site/after,/usr/local/share/nvim/site/after,/var/lib/flatpak/exports/share/nvim/site/after,~/.local/share/flatpak/exports/share/nvim/site/after,~/.local/share/nvim/site/after,/etc/xdg/nvim/after,~/.config/kdedefaults/nvim/after,~/.config/nvim/after,/usr/share/vim/vimfiles,/usr/share/vim/vimfiles/after
set scrolloff=10
set sessionoptions=blank,buffers,curdir,folds,help,tabpages,winsize,terminal,globals,options,localoptions
set shiftwidth=4
set sidescrolloff=10
set smartcase
set softtabstop=4
set splitright
set statusline=%#CurSearch#\ %(%{%toupper(mode())%}\ %*%)%(%#CursorLine#\ î­ \ %f\ %*%)%(%#CursorLine#\ %m%r%w%q%a\ %*%)%<%(\ îœ¥\ %{%luaeval(\"get_git()\")%}\ %)\ %{%\ v:lua.vim.diagnostic.status()\ %}\ %=\ %(\ ïˆ³\ %{%luaeval(\"get_lsp_name()\")%}\ %)%(\ %{%v:lua.vim.lsp.status()%}\ %)%(\ î«¨\ %Y\ %)%#CursorLine#\ x:\ %v\ y:\ %l\ %*%#CurSearch#\ %p%%\ %*
set tabline=%!TabbyRenderTabline()
set tabstop=4
set termguicolors
set title
set titlestring=%(%h%)%(%m%)\ %t
set undodir=~/.vim/undodir/
set undofile
set wildoptions=pum
set window=44
set winwidth=1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
doautoall SessionLoadPre
let TabbyTabNames = "[]"
silent only
silent tabonly
cd ~/Projects/gamedev/fearful_stars
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess+=aoO
badd +37 src/main.cpp
badd +190 term://~/Projects/gamedev/fearful_stars//29586:/bin/bash
badd +1 src/gameplay/projectile/basic/basic_projectile.cpp
badd +1 include/raylib.h
badd +14 ~/Projects/gamedev/fearful_stars/src/engine/background_man.cpp
badd +38 src/engine/background_man.hpp
argglobal
%argdel
$argadd .
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/engine/background_man.hpp
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt ~/Projects/gamedev/fearful_stars/src/engine/background_man.cpp
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal busy=0
setlocal cindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinscopedecls=public,protected,private
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,:///,://
setlocal commentstring=//\ %s
setlocal complete=.,w,b,u,t
setlocal completefunc=
setlocal completeslash=
setlocal concealcursor=
setlocal conceallevel=0
setlocal nocopyindent
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal cursorlineopt=both
setlocal define=^\\s*#\\s*define
setlocal nodiff
setlocal eventignorewin=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
set foldcolumn=2
setlocal foldcolumn=2
setlocal foldenable
set foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldignore=#
set foldlevel=99
setlocal foldlevel=99
setlocal foldmarker={{{,}}}
set foldmethod=indent
setlocal foldmethod=indent
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=v:lua.vim.lsp.formatexpr()
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatoptions=jcroql
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=^\\s*#\\s*include
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal lhistory=10
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispoptions=
setlocal nolist
setlocal makeprg=cmake\ --build\ ./build\ -j10\ --config\ Debug
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=v:lua.vim.lsp.omnifunc
setlocal path=.,/usr/include,,
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal scrollback=-1
setlocal noscrollbind
setlocal shiftwidth=4
setlocal signcolumn=auto
setlocal nosmartindent
setlocal nosmoothscroll
setlocal softtabstop=4
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\\t\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statuscolumn=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=4
setlocal tagfunc=v:lua.vim.lsp.tagfunc
setlocal textwidth=0
setlocal undofile
setlocal varsofttabstop=
setlocal vartabstop=
setlocal winblend=0
setlocal nowinfixbuf
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal winhighlight=
setlocal wrap
setlocal wrapmargin=0
35
sil! normal! zo
38
sil! normal! zo
38
sil! normal! zo
38
sil! normal! zo
38
sil! normal! zo
38
sil! normal! zo
38
sil! normal! zo
let s:l = 39 - ((21 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 39
normal! 036|
tabnext
argglobal
if bufexists(fnamemodify("term://~/Projects/gamedev/fearful_stars//29586:/bin/bash", ":p")) | buffer term://~/Projects/gamedev/fearful_stars//29586:/bin/bash | else | edit term://~/Projects/gamedev/fearful_stars//29586:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/Projects/gamedev/fearful_stars//29586:/bin/bash
endif
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=terminal
setlocal busy=0
setlocal nocindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinscopedecls=public,protected,private
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-,fb:â€¢
setlocal commentstring=
setlocal complete=.,w,b,u,t
setlocal completefunc=
setlocal completeslash=
setlocal concealcursor=
setlocal conceallevel=0
setlocal nocopyindent
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal cursorlineopt=both
setlocal nodiff
setlocal eventignorewin=
setlocal expandtab
if &filetype != ''
setlocal filetype=
endif
setlocal fixendofline
set foldcolumn=2
setlocal foldcolumn=0
setlocal foldenable
set foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldexpr=v:lua.vim.treesitter.foldexpr()
setlocal foldignore=#
set foldlevel=99
setlocal foldlevel=99
setlocal foldmarker={{{,}}}
set foldmethod=indent
setlocal foldmethod=indent
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatoptions=tcqj
setlocal iminsert=0
setlocal imsearch=-1
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal lhistory=10
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispoptions=
setlocal nolist
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal nomodifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal scrollback=10000
setlocal noscrollbind
setlocal shiftwidth=4
set signcolumn=no
setlocal signcolumn=no
setlocal nosmartindent
setlocal nosmoothscroll
setlocal softtabstop=4
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\\t\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statuscolumn=
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != ''
setlocal syntax=
endif
setlocal tabstop=4
setlocal tagfunc=
setlocal textwidth=0
setlocal undofile
setlocal undolevels=-1
setlocal varsofttabstop=
setlocal vartabstop=
setlocal winblend=0
setlocal nowinfixbuf
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal winhighlight=StatusLine:StatusLineTerm,StatusLineNC:StatusLineTermNC
setlocal nowrap
setlocal wrapmargin=0
let s:l = 190 - ((41 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 190
normal! 02|
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=1
set shortmess=ltToOCF
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
