rmdir /s /q out
rmdir /s /q build
mkdir out build

wszst create Event --dest out/Event.szs

wbmgt encode text/Menu_E.txt --dest build/Menu_E.bmg
wbmgt encode text/Menu_G.txt --dest build/Menu_G.bmg
wbmgt encode text/Menu_J.txt --dest build/Menu_J.bmg
wbmgt encode text/Menu_U.txt --dest build/Menu_U.bmg

wbmgt encode text/Race_E.txt --dest build/Race_E.bmg
wbmgt encode text/Race_G.txt --dest build/Race_G.bmg
wbmgt encode text/Race_J.txt --dest build/Race_J.bmg
wbmgt encode text/Race_U.txt --dest build/Race_U.bmg

md build\Event\message

copy text\Common_E.bmg build\Event\message\Common.bmg
copy build\Menu_E.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Event_E.szs
copy text\Common_G.bmg build\Event\message\Common.bmg
copy build\Menu_G.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Event_G.szs
copy text\Common_J.bmg build\Event\message\Common.bmg
copy build\Menu_J.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Event_J.szs
copy text\Common_U.bmg build\Event\message\Common.bmg
copy build\Menu_U.bmg build\Event\message\Menu.bmg
wszst create build/Event --dest out/Event_U.szs

copy out\Event_E.szs out\MenuOther_E.szs
copy out\Event_G.szs out\MenuOther_G.szs
copy out\Event_J.szs out\MenuOther_J.szs
copy out\Event_U.szs out\MenuOther_U.szs

copy out\Event_E.szs out\Channel_E.szs
copy out\Event_G.szs out\Channel_G.szs
copy out\Event_J.szs out\Channel_J.szs
copy out\Event_U.szs out\Channel_U.szs

mkdir base\Race_E.d\button\ctrl base\Race_G.d\button\ctrl base\Race_J.d\button\ctrl base\Race_U.d\button\ctrl
copy base\AfterMenuOfflineEvent.brctr base\Race_E.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_G.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_J.d\button\ctrl\AfterMenuOfflineEvent.brctr
copy base\AfterMenuOfflineEvent.brctr base\Race_U.d\button\ctrl\AfterMenuOfflineEvent.brctr

copy base\PauseMenuOfflineEvent.brctr base\Race_E.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_G.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_J.d\button\ctrl\PauseMenuOfflineEvent.brctr
copy base\PauseMenuOfflineEvent.brctr base\Race_U.d\button\ctrl\PauseMenuOfflineEvent.brctr

copy text\Common_E.bmg base\Race_E.d\message\Common.bmg
copy build\Menu_E.bmg base\Race_E.d\message\Menu.bmg
copy build\Race_E.bmg base\Race_E.d\message\Race.bmg
wszst create base\Race_E.d --dest out/Race_E.szs
copy text\Common_G.bmg base\Race_G.d\message\Common.bmg
copy build\Menu_G.bmg base\Race_G.d\message\Menu.bmg
copy build\Race_G.bmg base\Race_G.d\message\Race.bmg
wszst create base\Race_G.d --dest out/Race_G.szs
copy text\Common_J.bmg base\Race_J.d\message\Common.bmg
copy build\Menu_J.bmg base\Race_J.d\message\Menu.bmg
copy build\Race_J.bmg base\Race_J.d\message\Race.bmg
wszst create base\Race_J.d --dest out/Race_J.szs
copy text\Common_U.bmg base\Race_U.d\message\Common.bmg
copy build\Menu_U.bmg base\Race_U.d\message\Menu.bmg
copy build\Race_U.bmg base\Race_U.d\message\Race.bmg
wszst create base\Race_U.d --dest out/Race_U.szs

