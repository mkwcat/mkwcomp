rmdir /s /q out
rmdir /s /q build
mkdir out build

wszst create Event --dest out/Event.szs

wbmgt encode text/Menu_E.txt --dest build/Menu_E.bmg
wbmgt encode text/Menu_F.txt --dest build/Menu_F.bmg
wbmgt encode text/Menu_G.txt --dest build/Menu_G.bmg
wbmgt encode text/Menu_I.txt --dest build/Menu_I.bmg
wbmgt encode text/Menu_J.txt --dest build/Menu_J.bmg
wbmgt encode text/Menu_K.txt --dest build/Menu_K.bmg
wbmgt encode text/Menu_M.txt --dest build/Menu_M.bmg
wbmgt encode text/Menu_Q.txt --dest build/Menu_Q.bmg
wbmgt encode text/Menu_S.txt --dest build/Menu_S.bmg
wbmgt encode text/Menu_U.txt --dest build/Menu_U.bmg

wbmgt encode text/Race_E.txt --dest build/Race_E.bmg
wbmgt encode text/Race_F.txt --dest build/Race_F.bmg
wbmgt encode text/Race_G.txt --dest build/Race_G.bmg
wbmgt encode text/Race_I.txt --dest build/Race_I.bmg
wbmgt encode text/Race_J.txt --dest build/Race_J.bmg
wbmgt encode text/Race_K.txt --dest build/Race_K.bmg
wbmgt encode text/Race_M.txt --dest build/Race_M.bmg
wbmgt encode text/Race_Q.txt --dest build/Race_Q.bmg
wbmgt encode text/Race_S.txt --dest build/Race_S.bmg
wbmgt encode text/Race_U.txt --dest build/Race_U.bmg

md build\Event\message

copy text\Common_E.bmg build\Event\message\Common.bmg
copy build\Menu_E.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_E.szs
copy text\Common_F.bmg build\Event\message\Common.bmg
copy build\Menu_F.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_F.szs
copy text\Common_G.bmg build\Event\message\Common.bmg
copy build\Menu_G.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_G.szs
copy text\Common_I.bmg build\Event\message\Common.bmg
copy build\Menu_I.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_I.szs
copy text\Common_J.bmg build\Event\message\Common.bmg
copy build\Menu_J.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_J.szs
copy text\Common_K.bmg build\Event\message\Common.bmg
copy build\Menu_K.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_K.szs
copy text\Common_M.bmg build\Event\message\Common.bmg
copy build\Menu_M.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_M.szs
copy text\Common_Q.bmg build\Event\message\Common.bmg
copy build\Menu_Q.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_Q.szs
copy text\Common_S.bmg build\Event\message\Common.bmg
copy build\Menu_S.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_S.szs
copy text\Common_U.bmg build\Event\message\Common.bmg
copy build\Menu_U.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Message_U.szs

mkdir base\Race_E.d\button\ctrl base\Race_F.d\button\ctrl base\Race_G.d\button\ctrl
mkdir base\Race_I.d\button\ctrl base\Race_J.d\button\ctrl base\Race_M.d\button\ctrl
mkdir base\Race_Q.d\button\ctrl base\Race_S.d\button\ctrl base\Race_U.d\button\ctrl
mkdir base\Race_K.d\button\ctrl
copy base\AfterMenuOfflineEvent.brctr base\Race_E.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_F.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_G.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_I.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_J.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_K.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_M.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_Q.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_S.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_U.d\button\ctrl\AfterMenuOfflineEvent.brctr

copy base\PauseMenuOfflineEvent.brctr base\Race_E.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_F.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_G.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_I.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_J.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_K.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_M.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_Q.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_S.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_U.d\button\ctrl\PauseMenuOfflineEvent.brctr

copy text\Common_E.bmg base\Race_E.d\message\Common.bmg
copy build\Menu_E.bmg base\Race_E.d\message\Menu.bmg
copy build\Race_E.bmg base\Race_E.d\message\Race.bmg
wszst create base\Race_E.d --dest out/Race_E.szs
copy text\Common_F.bmg base\Race_F.d\message\Common.bmg
copy build\Menu_F.bmg base\Race_F.d\message\Menu.bmg
copy build\Race_F.bmg base\Race_F.d\message\Race.bmg
wszst create base\Race_F.d --dest out/Race_F.szs
copy text\Common_G.bmg base\Race_G.d\message\Common.bmg
copy build\Menu_G.bmg base\Race_G.d\message\Menu.bmg
copy build\Race_G.bmg base\Race_G.d\message\Race.bmg
wszst create base\Race_G.d --dest out/Race_G.szs
copy text\Common_I.bmg base\Race_I.d\message\Common.bmg
copy build\Menu_I.bmg base\Race_I.d\message\Menu.bmg
copy build\Race_I.bmg base\Race_I.d\message\Race.bmg
wszst create base\Race_I.d --dest out/Race_I.szs
copy text\Common_J.bmg base\Race_J.d\message\Common.bmg
copy build\Menu_J.bmg base\Race_J.d\message\Menu.bmg
copy build\Race_J.bmg base\Race_J.d\message\Race.bmg
wszst create base\Race_J.d --dest out/Race_J.szs
copy text\Common_K.bmg base\Race_K.d\message\Common.bmg
copy build\Menu_K.bmg base\Race_K.d\message\Menu.bmg
copy build\Race_K.bmg base\Race_K.d\message\Race.bmg
wszst create base\Race_K.d --dest out/Race_K.szs
copy text\Common_M.bmg base\Race_M.d\message\Common.bmg
copy build\Menu_M.bmg base\Race_M.d\message\Menu.bmg
copy build\Race_M.bmg base\Race_M.d\message\Race.bmg
wszst create base\Race_M.d --dest out/Race_M.szs
copy text\Common_Q.bmg base\Race_Q.d\message\Common.bmg
copy build\Menu_Q.bmg base\Race_Q.d\message\Menu.bmg
copy build\Race_Q.bmg base\Race_Q.d\message\Race.bmg
wszst create base\Race_Q.d --dest out/Race_Q.szs
copy text\Common_S.bmg base\Race_S.d\message\Common.bmg
copy build\Menu_S.bmg base\Race_S.d\message\Menu.bmg
copy build\Race_S.bmg base\Race_S.d\message\Race.bmg
wszst create base\Race_S.d --dest out/Race_S.szs
copy text\Common_U.bmg base\Race_U.d\message\Common.bmg
copy build\Menu_U.bmg base\Race_U.d\message\Menu.bmg
copy build\Race_U.bmg base\Race_U.d\message\Race.bmg
wszst create base\Race_U.d --dest out/Race_U.szs

copy text\Common_E.bmg base\Title_E.d\message\Common.bmg
copy text\Common_F.bmg base\Title_F.d\message\Common.bmg
copy text\Common_G.bmg base\Title_G.d\message\Common.bmg
copy text\Common_I.bmg base\Title_I.d\message\Common.bmg
copy text\Common_J.bmg base\Title_J.d\message\Common.bmg
copy text\Common_K.bmg base\Title_K.d\message\Common.bmg
copy text\Common_M.bmg base\Title_M.d\message\Common.bmg
copy text\Common_Q.bmg base\Title_Q.d\message\Common.bmg
copy text\Common_S.bmg base\Title_S.d\message\Common.bmg
copy text\Common_U.bmg base\Title_U.d\message\Common.bmg

copy build\Menu_E.bmg base\Title_E.d\message\Menu.bmg
copy build\Menu_F.bmg base\Title_F.d\message\Menu.bmg
copy build\Menu_G.bmg base\Title_G.d\message\Menu.bmg
copy build\Menu_I.bmg base\Title_I.d\message\Menu.bmg
copy build\Menu_J.bmg base\Title_J.d\message\Menu.bmg
copy build\Menu_K.bmg base\Title_K.d\message\Menu.bmg
copy build\Menu_M.bmg base\Title_M.d\message\Menu.bmg
copy build\Menu_Q.bmg base\Title_Q.d\message\Menu.bmg
copy build\Menu_S.bmg base\Title_S.d\message\Menu.bmg
copy build\Menu_U.bmg base\Title_U.d\message\Menu.bmg

wszst create base\Title_E.d --dest out/Title_E.szs
wszst create base\Title_F.d --dest out/Title_F.szs
wszst create base\Title_G.d --dest out/Title_G.szs
wszst create base\Title_I.d --dest out/Title_I.szs
wszst create base\Title_J.d --dest out/Title_J.szs
wszst create base\Title_K.d --dest out/Title_K.szs
wszst create base\Title_M.d --dest out/Title_M.szs
wszst create base\Title_Q.d --dest out/Title_Q.szs
wszst create base\Title_S.d --dest out/Title_S.szs
wszst create base\Title_U.d --dest out/Title_U.szs

wszst create Title.d --dest out/Title.szs
