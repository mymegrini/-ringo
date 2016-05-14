#include "banner.h"

#include <stdio.h>

const char *banner[] = 
{
  "\n"
    " _____ _\n"
    "| __  |_|___ ___ ___\n"
    "|    -| |   | . | . |\n"
    "|__|__|_|_|_|_  |___|\n"
    "            |___|\n",
  " ______ __                    \n"
    "|   __ \\__|.-----.-----.-----.\n"
    "|      <  ||     |  _  |  _  |\n"
    "|___|__|__||__|__|___  |_____|\n"
    "                 |_____|   \n",
  "    ___       ___       ___       ___       ___   \n"
    "   /\\  \\     /\\  \\     /\\__\\     /\\  \\     /\\  \\  \n"
    "  /::\\  \\   _\\:\\  \\   /:| _|_   /::\\  \\   /::\\  \\ \n"
    " /::\\:\\__\\ /\\/::\\__\\ /::|/\\__\\ /:/\\:\\__\\ /:/\\:\\__\\\n"
    " \\;:::/  / \\::/\\/__/ \\/|::/  / \\:\\:\\/__/ \\:\\/:/  /\n"
    "  |:\\/__/   \\:\\__\\     |:/  /   \\::/  /   \\::/  / \n"
    "   \\|__|     \\/__/     \\/__/     \\/__/     \\/__/  \n",
  "                                         \n"
    "_|_|_|    _|                                \n"
    "_|    _|      _|_|_|      _|_|_|    _|_|    \n"
    "_|_|_|    _|  _|    _|  _|    _|  _|    _|  \n"
    "_|    _|  _|  _|    _|  _|    _|  _|    _|  \n"
    "_|    _|  _|  _|    _|    _|_|_|    _|_|    \n"
    "                              _|            \n"
    "                          _|_|           \n",
  "_____________                      \n"
    "___  __ \\__(_)_____________ ______ \n"
    "__  /_/ /_  /__  __ \\_  __ `/  __ \n"
    "_  _, _/_  / _  / / /  /_/ // /_/ /\n"
    "/_/ |_| /_/  /_/ /_/_\\__, / \\____/ \n"
    "                    /____/         \n",
  "    _/_/_/    _/                               \n"
    "   _/    _/      _/_/_/      _/_/_/    _/_/    \n"
    "  _/_/_/    _/  _/    _/  _/    _/  _/    _/   \n"
    " _/    _/  _/  _/    _/  _/    _/  _/    _/    \n"
    "_/    _/  _/  _/    _/    _/_/_/    _/_/       \n"
    "                             _/                \n",
  " ______ _____ __   _  ______  _____ \n"
    " |_____/   |   | \\  | |  ____ |     |\n"
    " |    \\_ __|__ |  \\_| |_____| |_____|\n",
  NULL
};

const char *nicolas[] = {
  "                                                \n"
    "                                                \n"
    "                                                \n"
    "                  `,;',                         \n"
    "                `;++++++++;:`                   \n"
    "             :+''+++++#+#+++++;                 \n"
    "           `',;++++++#+###++++++,               \n"
    "           :';'++++#++++##+##+##+;              \n"
    "          ,'''++++++++#++#+++++++++             \n"
    "         .'''++++++++++++#++++++++++            \n"
    "        `;''+'+++++++++++++++++++++++           \n"
    "       `'''''++++++++++++++++++++++++'          \n"
    "       ,;''+''++++++++++++++++++++++++,         \n"
    "      `:;''''+'+'+++++++++++++++++++++'         \n"
    "      ;;''''''''''+'+++++++++++++++++++.        \n"
    "     `;;''''''''''++'''++++++++++++++++'`       \n"
    "     ;;;'''''''+''''';;;;''+++++++++++++;.      \n"
    "    `:;;''''''++';:;';::;:;;'++++++##+++'       \n"
    "    ,;;;''''+'+++;:::;:;::::;;+++++#+++++       \n"
    "    ';;'''++''++++;:::::::::;;'+++###++++       \n"
    "   `;;;;'''++;';'''::,,:,,:::;;'+++#####+,      \n"
    "   ,:;;;'''+';;;:::;:::::::;;;;''+######+'      \n"
    "   ::';;''++';::::,::::::::;;;;;;'#######+.     \n"
    "   ::';;'';';;:;::,,::,,::::;;;;;'+######++`    \n"
    "   ;;;:;;'';::::::,,,:,,,::::;;;''+#######`;    \n"
    "  `;'':;;;';;;';;;;::,,,,,,::;;'+++#######;     \n"
    "  `';';;;;'''+++++++;::,,:;;+######+######;     \n"
    "  .;'+'';;'+';;;;+++';:,,:;++##;:;'+######:     \n"
    "  ,;''''';+';::::;;;;;:,::''';;;;;'++#####+     \n"
    "  .':''+';';::;'+';:;;:::;;;'''+';''+#####+     \n"
    "  :+'++'';';;''+'+:';;;::;;;+###++''+#####+     \n"
    "   :++++';;;'++:++:';;;::;;+++#''#''+######     \n"
    "   .++++'';;;;;'';;;;;::;;'''''+++''+##@##;     \n"
    "   ,++++'';:;;::::;;'';;;;''';';''''+#####:     \n"
    "   .++++'';;;:::,::;''';;'''';;'''''+#####      \n"
    "   .+++'+'';;;::,:;''';;''''';;'';;'+####+      \n"
    "   `++++++';:;::::;''';;;'+'''';;;';+####+      \n"
    "   `'++++#;;::;:::;'';;;;''''';'''''+#####      \n"
    "    '#####';;;;;::;''';;;''+''''''''+#@#@#:     \n"
    "    ,#####';;;;;:;;''+'''#'+'''''+'++###@'      \n"
    "    `##++#'';;;;:;'''+'''+++''''''+++####,      \n"
    "     +#+'#+';;;;;''''';;'++++'''+'++#####       \n"
    "     .+;'++'''';;''++''''+++++''++++####,       \n"
    "      ,+'''';'';'+'''''+''++++++++++++@+        \n"
    "       +''';;'''''''+++++++++++++++++@@,        \n"
    "        ##'''''''++++#######++++++++@##         \n"
    "        ##''''''''+++++++++##+++++++#':         \n"
    "        :##'''''''''''+++++++++++++#@#          \n"
    "         +#'''''''''''++++++++++++#@#,          \n"
    "         +#+''+'''''''+''++++++++++@#:          \n"
    "         +##''+'+'''''''''++++++++@@#;          \n"
    "         '##''''+''''''''+++++++++@@#'          \n"
    "         :#++'''''''';;'''+++#+'##@@;;+         \n"
    "          #''++''+''''''''+++#+###@#:           \n"
    "          ;''+++++++'''''+++#+#####@.           \n"
    "           ;'+++####+++++#########':            \n"
    "           ;+++'#+#####@###########             \n"
    "           '+'''+#+#+#############'             \n"
    "           ++++'+##+++#+'+########.             \n"
    "           '+++++#++++++'+########:;'.          \n"
    "           #++++'++++++++#########@@@@'.        \n"
    "           +++++'###+++'+#########@@@@@'        \n"
    "     +####;+++++'+####+++##########@@@@@;       \n"
    "   ,###@#';+#++++++###+#############@@@@#       \n"
    "   ###@@'++##++++++#+++++###########@@@@@;      \n"
    "  '#'##+++####+++'+#+++++##########@@@@@@#      \n"
    "                                                \n",
",........,..,...,,,,,,,,,,,,,,.,,,....,,,,,,,,,,,,\n"
"`````````````````````````````````````````````````,\n"
"````````````````````..,.`````````````````````````:\n"
"`````````````````.;+++++++'';,```````````````````:\n"
"`````````````;+''+++++#####+++++',```````````````:\n"
"````````````;'''++++++####++##+++++.`````````````;\n"
"```````````''''+++++++##++#++++#++++'````````````;\n"
"`````````.'''+++++++++++++++++++++++++.``````````;\n"
".```````.;''''+++++++++++++++++++++++++,`.````.``;\n"
".```````;'''''++++++++++++++++++++++++++,``.`..``'\n"
".``````::'''''''''++++++++++++++++++++++'`.`...`.'\n"
". ````;;'''''''''''++'''+++++++++++++++++;......`'\n"
".````:;;''''''''';'''';;;;;'++++++++++++++;,.....'\n"
".` ``;;;''''''+++;:::;';:;::;;'+++++++++++'......'\n"
". ``:;;;'''+''++++';:::;;::::::;++++###++++......+\n"
".  `;::;'''++';''''';:,,:,,,:::;;'#+####+#+:.....'\n"
".` .:;;;''''';';;:,::::::::::;;;;;'+######++.....'\n"
". `,;;:;''''';;::::,,::::::::;:;;;''########+,,,,+\n"
",`.;;;:;'''';:;::::,,,,,,,::,:;;;'''+#######::,,,+\n"
".``;:;;;';;;;''''++'::,,,,,:::;''##++#######',,,,+\n"
".`.;;;;'';''++;;;+++';;;,,::'####;''++######;,,,,+\n"
".`.:'+''';'';:::::;;;;;:,::;'';;;;;;'+######+,,,,+\n"
".`.';+'+''';:;;'+#+';;;;::;;;''##++;;+#######,,,,+\n"
",``;;+'+';';;'+''++:'';;::;;';;##;#+''#######:,::+\n"
".``.++++';';;;;;'';;;;;:::;'';''+++'''+#####;::::+\n"
",``.++++''';;;;;,::;;';;;;;''';;;'''''+#####:::::+\n"
",``.++++++';;;;:,,::''''''''''';;';;;'+##@##:::::+\n"
". `.++++++';;;::,::;''';;:;+''';';';''+####+:::::+\n"
", `.++++##+;;;;;:::;;'';;;;'+''';'''''+#@#@#::::;+\n"
", `.,+####+';;;;;:;;''#'';++'';''''+'+####@+:::;;+\n"
",```.+##'##';;;;;:;'''+''''++''''''+++###@#;:;;;;+\n"
",``..,##'+#''';;;;'''+'';''++++'''++++##@#+;;;;;;#\n"
",```..,+''+'';;'''''''''+'+++++++++++'#+@+;;;;;;;+\n"
",``....;+'''';'''''''+++++++++++++++++#@@;;;;;;;;+\n"
",``.....###'''''''+#++++++#####++++++##'+;;;;;;;;#\n"
":``.....;##''''''''''++''+++++++++++#@##;;;;;;;;;+\n"
",`.......'#+'''''''''''++++++++++++++@@';;;;;;;;;#\n"
",.......,,##'''+'''''''''''+++++++++@@#;;;;;;;;;'#\n"
":.......,,##+'''''''''''''+++++++++#@@#;;;;;;;;''#\n"
",.......,,##'''''''''';;'''+++++++##@#;'';;;;''''#\n"
",........,;+''+++++''''''''++##+####@#;;;;;''''''#\n"
",........,,';'+++###++'++++#########;';;;;;''''''#\n"
",.....,,.,,,'+'++#+################'';;;;;;''''''#\n"
":......,,,,:+''+'++#++###++###+####+;;;;;;'''''''+\n"
":.....,,,,,:'+++++#++++++++########+;;;;;''''''''+\n"
",......,,,,:++++++#++++++++#########@@@@'''''''''+\n"
":....,,:;';:+++++'###+++++##+#######@@@@@+'''''''+\n"
":..,'###@#;;+++++'+###+++####+########@@@@+'''''''\n"
",,,###@@+++###++++++++++++############@@@@@'''''''\n"
":,+#+##+++###++++''+++'''++++++++###########''''''\n",

",.....,.,...,,..,,..,.,,,,,,.,,,,,,,,,,,..,,,.....,,,,,,,,,,,,,,,,,\n"
"`````````````````````````````````````````````````````````````````:,\n"
"```````````````````````````..,,``````````````````````````````````;:\n"
"```````````````````````.;++++++#+++'';:,`````````````````````````;,\n"
"`````````````````,'';''+++++++#+####+++++++',````````````````````;:\n"
"```````````````.;;'''+++++++####+###+++#++++++;.`````````````````':\n"
"``````````````,''''+++++++++++#++++#++++++#+++++'.```````````````':\n"
"````````````.''''''+++++++++++++++++++++++++++++++'.````````.````':\n"
".``````````:;'''''++++++++++++++++++++++++++++++++++,`.``````````':\n"
".`````````:;'''''''++++++++++++++++++++++++++++++++++;```.``..``.';\n"
", ```````;:;'''''''''+''++++++++++++++++++++++++++++++:.``.......';\n"
". ``````;;;'''''''+'''''++++''''+++++++++++++++++++++++,........`;;\n"
".  ````:;;;'''''''+''+''''''';;;;;;;''++++++++++++++++++;........;;\n"
". ````:'';;''''''+'+++';:,::;';::;::::;''+++++#+++++++++'....,...;;\n"
".  ``.';;;'''''+''++'++++;::::;;;::::::::;'+++++#####++++,.......;'\n"
".  ``;;;;;;''''+++;;';'''';;:,,,:,,,,:::;;;;'+++#######++',......;'\n"
".` ``;;;;;;'''''';;;;:::::::::::::::::;;;;;;;;'#########++:......;'\n"
".```,;;':;;'''''';;;:;;::,,::::,::::::;;:;;;;;'+##########+',..,,;'\n"
",```;';;;;;;'''';::::::,:,,,,,,,,,,::,:::;;;;''++#########+,:,,,,;'\n"
".```;''';;;;;;;;;''''+'+'';::,,,,,,,::;;;''+###++#########+:,,,,,;'\n"
".``,;;'+;'''''''+'';;;;++++';'':,,,::'+####+;;''+++########;,,,,,;'\n"
".``::'+';+'';'+';:::::::;;;;;;::,:::;''';;;;;;;;'++########;,,,,,;'\n"
"..`,'+++;'+'';';:;:;'+##+';;;;;::::;;;;''###++';;'+########',,,,,;+\n"
",.``;'++'++';'';;;'+';+++,;'';;:::;;;;+;;###;+#+'''#########,:,::''\n"
"..```++++++';';;;;;;;';';;;;;';:::;;'''''''++++'''+########::::::'+\n"
",.```+++'++''';;;;;:::,:::;;';;;;;;;'''';;;;'''''''+#######::::::'+\n"
",.``.+#+'++++'';;;;;::,:::;'''''''''''''';;;;;;;;''+###@##:::::::'+\n"
"..``.+#+'+++++';;;;::::::;;''';;;:;;++''''';;;;;'''+######:::::::'+\n"
",. `.;+++#+##+;;;;;;;::::;;'';;;;;;'''''''';'''''''+##@###+::::::++\n"
",. `..++##+###'';;;;;;::;;'''+#'';'#+'+';'''''''+'+##@##@#:::::;;++\n"
",. ``..###++##'';;;;;;;:;''''+'''''++++''''''''++++######+;:;;;;;++\n"
",```...;##';+#+'';;;;;;;''''+'';;''++++++''''++++++###@#+;:;;;;;;++\n"
",.```...,''''++'';';';;'''+'''''++'++++++++++++++++#+@@+;;;;;;;;;++\n"
",.``.....:#+'+''';''''''''+'+++++++++++++++++++++++#@#+;;;;;;;;;;++\n"
",.`.......,###''''''''''+##++++++++######+++++++++@#'#;;;;;;;;;;;+#\n"
":```.......+##+'''''''''''''++''''++++++++++++++##@+#';;;;;;;;;;;++\n"
":`..........'##'''''''''''''''+++++++++++++++++++@@#';;;;;;;;;;;;+#\n"
",.........,,,###''''+'''''''''''''''++++++++++++@@#+;;;;;;;;;;';'++\n"
":`........,,,+##'';''''''''''''''''++++++++++++@@@#@;;;;;;;;;;'''++\n"
",.........,,,'##''''''+''''''';;''''+++++#+++##@@@#;'';;;;;'''''''#\n"
",.........,.,,+#''+++'''+++'''''''''+++##++####@@@#;;;;;;;''''''''+\n"
",..........,,,,+;'++++#####++''+++++############;';;;;;;;;''''''''+\n"
",........,,,,,,,'++'+++########################'+;;;;;';;'''''''''#\n"
":.......,,,,,,,:++''+'+++##++####+++####+######';;;;;;;;''''''''''#\n"
":......,,,,,,,,:'+++++++###+++++++'+###########';;;;''''''''''''''#\n"
",.......,,,,,,,;++++++'++#+++++++++#############@@@@@+''''''''''''#\n"
":,...,,,,:;''':;+++++++'+###+++++++##+##########@@@@@@@'''''''''''#\n"
":...,:#######';'+++++++'+######+++################@@@@@@+'''''''''#\n"
",,,:#+#####++++###+++++'++#+++++++################@@@@@@@#''''''''#\n"
":,:##++##+++++####+++++'''++++'''++++++++++################'''''''#\n",

",...........,.........,...................,..,,,,,\n"
"`````````````````````````````````````````````````:\n"
"`````````````````.'++++#+++'':.``````````````````:\n"
"````````````;,;'++++#+####+#++++++.``````````````;\n"
"```````````''''++++++++++##+++++#+++'````````````;\n"
"`````````;''''++++++++++++++++++++++++'``````````;\n"
".``````.;'''''++++++++++++++++++++++++++,````..`.'\n"
". ````,;;''''+';'''+'++++++++++++++++++++.......`'\n"
".````:;;'''''''+';'''';;:;;''+++++++++++++',.....'\n"
".  ``';;'''++'++++;:::;;;::::;;'+++++###++'......'\n"
".  `;:;;'''++';';'';::,,:,,,:::;;'######+++:.....'\n"
".``:;';;''''';;:::::,::::::::;;;';;+#######+:...,'\n"
",`.;;;:;'''';:;::,:,,,,,,,:::::;;;''+#######;,,,,+\n"
".``;:;;;;;'''++'+++++;::,,::;+####++#+######',,,,+\n"
".`.:'+''';'';::::;;;;;;:,::;;;;;;;;;'+######+,,,,+\n"
",`.''+''';';;;;++'#:;;;;::;;;';+#+#+''#######,,,:+\n"
".``.+'+++;';;;;;;';;;';;:;;'';''+++'''+###@#;::::+\n"
",``.+++'+'';;;::,::;'''';''''';;;;'';'+#####:::::+\n"
", `.++'+++';;;::,::;;'';;:;++''';';;''+####+:::::+\n"
", `.;#####+';;;;;:;;'''';;''''''''''''#@@@@#:::;;+\n"
",```.+#+'##';;;;;:;'''+;';'+++'''''+++#####;:;;;;+\n"
",``...++'+#';;;;;;''++''''+++++++++++'#+@#;;;;;;;#\n"
",``....:#'+'';''''''''++++++++++++++++##@;;;;;;;;+\n"
":```....+##'''';'''+++++'+++##+++++++#+';;;;;;;;;#\n"
",`.......'##'''''''''''++++++++++++++@@;;;;;;;;;;#\n"
",.......,,##+''''''''''''''+++++++++@@#;;;;;;;'''#\n"
",......,,,##'''''''''';''''+++++++##@#;'';;;;;'''#\n"
",.......,,,+''+++#+++'''''+++#######++;;;;;;'''''#\n"
",......,,,,,++'++#########@########'+;;;;;;''''''#\n"
",...,,.,,,,,+++++++++++++'+########+;;;';''''''''+\n"
",...,.,,,,,:++++++#++++++++#########@@@@'''''''''+\n"
":...,+####+;+++++'+####+++###########@@@@@'''''''+\n"
",,:#+#@@+++###++++++++++++############@@@@@+''''''\n"
":,;;,;:;;;:;;;;';;;'''''''''''++++++++++++++++++++\n"


};

