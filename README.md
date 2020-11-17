# Reservation-system
<h1>Domácí úkol č.1: Rezervačný systém</h1>
<h2 id="ciele">Ciele</h2>
<p>Pri tejto úlohe sa naučíte, že práca s typmi ako <code>std::string</code> a <code>std::vector</code> v C++ veľa vecí zjednodušuje, že vstupov a výstupov sa nemusíte báť, a hlavne kde a ako správne používať <code>const</code> a referencie. Kvôli tomu je v tejto úlohe zakázané brať argumenty kopírovaním a následne použiť <code>std::move</code> (táto info je hlavne pre tých z vás, ktorí sú v jazyku C++ už pokročilí). Triedam sa budeme venovať len zbežne, ich hlavou úlohou bude sprehľadnenie nášho kódu.</p>
<h2 id="pravidlá">Pravidlá</h2>
<p>V zadaní nie je nikde explicitne povedané (až na pár výnimiek), ktorá metóda, atribút či parameter je konštantný, a kedy máte použiť referencie - <strong>je na vás, aby ste na to prišli sami</strong>. Tieto pravidlá boli preberané na prednáškach, riaďte sa nimi. Testy overia, či je vaše riešenie správne.</p>
<p>Verejné rozhranie popísané v tejto úlohe <strong>musíte</strong> dodržať, a to úplne presne, vrátane:</p>
<ul>
<li>pri verejných atribútoch: typ aj meno</li>
<li>pri metódach: typ atribútov, návratový typ a meno</li>
<li>navyše nepridávajte žiadne dodatočné <strong>verejné</strong> metódy ani atribúty (privátne si pridávať môžete)</li>
</ul>
<p>Pri vypisovaní na štandardný výstup / chybový výstup používajte výhradne C++ prostriedky vstupu <code>std::cout</code>, <code>std::cerr</code>, a pre načítanie zas <code>std::cin</code>.</p>
<p>V tejto úlohe budeme navyše pracovať s časovými intervalmi. Intervaly budeme vždy zadávať zľava uzavreté a sprava otvorené, a teda <em>[from, to)</em>. Ak sa teda spýtam, či je učebňa v časovom intervale <em>from-to</em> voľná, chcem vedieť, či je voľná od hodiny <em>from</em> vrátane, po hodinu <em>to</em>. To, či je učebňa od času <em>to</em> prázdna ma už nezaujíma.</p>
<p><em>Príklad:</em> Ak poviem, že učebňa je plná v intervale <em>i1-i2</em>, učebňa stále môže byť voľná pre interval <em>i2-i3</em> (i1 &lt; i2 &lt; i3).</p>
<p>Nezabudnite si taktiež strážiť korektnosť vstupov. Nekorektný vstup spôsobí, že volaná metóda skončí neúspešne (vždy je definované, čo to pre danú metódu znamená).</p>
<h2 id="predstavenie-úlohy">Predstavenie úlohy</h2>
<p>Určite viete, že vytvoriť si ideálny rozvrh nie je vždy jednoduché. Vybrať správnu miesnosť, správny čas - niekto preferuje rána, niekto je aktívnejší večer.</p>
<p>V tejto úlohe si vyskúšame vytvoriť jednoduchý rezervačný systém. Ten sa bude skladať zo <strong>4 tried:</strong> <code>Room</code>, <code>Course</code>, <code>Reservation</code> a <code>ReservationSystem</code>.</p>
<h2 id="triedy">Triedy</h2>
<h3 id="room">Room</h3>
<p>Trieda <code>Room</code> bude predstavovať miestnosť - môžete si predstaviť učebňu. Učebňa bude definovaná týmto <em>verejným</em> rozhraním:</p>
<p>Atribútmi:</p>
<ul>
<li>svojím menom <strong>name</strong> (<code>std::string</code>), ktorým bude zároveň unikátne identifikovaná (napríklad A217). Tento atribút bude verejný, avšak <strong>nemenný</strong>.</li>
</ul>
<p>Metódami:</p>
<ul>
<li><code>bool isFree(int from, int to)</code>, ktorá vráti <code>true</code> ak je miestnosť v <em>celom</em> časovom intervale <em>from-to</em> voľná a <code>false</code> ak je obsadená, alebo ak bola metóda neúspešná.</li>
</ul>
<p><em>Príklad: pre úplne prázdnu miestnosť musí platiť, že je voľná v intervale 0-24.</em></p>
<ul>
<li><code>int isFreeFor(int duration)</code>, ktorá vráti:
<ul>
<li>ak existuje časový úsek dĺžky <code>duration</code>, počas ktorého je miestnosť neprerušene voľná, tak začiatok tohto úseku</li>
<li>ak taký úsek nie je, alebo je metóda neúspešná, vráti -1</li>
<li>v prípade, že je takýchto úsekov viac, vráťte ľubovoľný</li>
</ul></li>
</ul>
<p><em>Príklad: Ak sa pre úplne prázdnu miestnosť spýtame isFreeFor(3) môžeme ako výsledok dostať ľubovoľné celé číslo v intervale [0, 21]</em></p>
<ul>
<li><p><code>bool occupy(int from, int to)</code>, ktorá vráti <code>true</code> ak sa podarilo rezervovať miestnosť v <em>celom</em> časovom intervale <em>from-to</em>, <code>false</code> v prípade neúspechu. Zjavne musí platiť <code>isFree =&gt; occupy</code>.</p></li>
<li><p><code>void print()</code>, ktorá vypíše info o miestnosti vo formáte: <code>Room: &lt;name&gt;\n</code></p></li>
<li><p><code>void schedule()</code>, ktorá vypíše info obsadenosti miestnosti, a to tak, že ak je miestnosť v danej hodine obsadená, vypíše <code>X</code>, ak voľná tak <code>_</code>.</p></li>
</ul>
<p><em>Príklad: Ak sa pre úplne plnú miestnosť spýtame schedule, na štandardný výstup sa vypíše:</em> <code>XXXXXXXXXXXXXXXXXXXXXXXX\n</code>. <em>Ak sa pre miestnosť, ktorá je rezervovaná len v intervale 0-3 spýtame schedule, na štandardný výstup sa vypíše:</em> <code>XXX_____________________\n</code>.</p>
<p>Trieda <code>Room</code> bude teda obohatená o vašu internú informáciu, kedy je miestnosť voľná. Miestnosť musí byť rezervovateľná v hodinových intervaloch, celých 24 hodín. Tento atribút bude privátny, a teda jeho názov a formát si môžete vybrať sami. Odporúčame vám využiť <code>std::vector</code> prípadne <code>std::array</code>, výber je však čisto na vás. (Tip: odvážnym môže stačit jeden <code>uint32_t</code>).</p>
<p>Navyše, inštancia prázdnej triedy Room sa musí dať vytvoriť nasledovne: <code>Room room(name);</code></p>
<h3 id="course">Course</h3>
<p>Trieda <code>Course</code> bude predstavovať predmet - môžete si predstaviť napríklad náš predmet. Predmet bude definovaný:</p>
<p>Atribúty:</p>
<ul>
<li>svojím kódom <strong>code</strong> (<code>std::string</code>), ktorým bude zároveň unikátne identifikovaný (napríklad PB161). Tento atribút bude verejný, avšak <strong>nemenný</strong>.</li>
<li>svojím učiteľom <strong>teacher</strong> (<code>std::string</code>). Tento atribút bude verejný, avšak <strong>nemenný</strong>.</li>
</ul>
<p>Metódy:</p>
<ul>
<li><code>void print()</code>, ktorá vypíše info o miestnosti vo formáte:
<ul>
<li>ak je atribút <strong>teacher</strong> neprázdny: <code>Course: &lt;code&gt; [Teacher: &lt;teacher&gt;]\n</code></li>
<li>ak je atribút <strong>teacher</strong> prázdny: (<a href="https://en.cppreference.com/w/cpp/string/basic_string/empty">std::string::empty</a>) <code>Course: &lt;code&gt;\n</code></li>
</ul></li>
</ul>
<p>Navyše, inštancia triedy Course sa musí dať vytvoriť nasledovne: <code>Course course(code, teacher);</code></p>
<h3 id="reservation">Reservation</h3>
<p>Trieda <code>Reservation</code> bude predstavovať výsledok úspešného požiadavku na rezerváciu. Rezervácia bude definovaná týmto verejným rozhraním (všetky atribúty sú automaticky <strong>nemenné</strong>):</p>
<p>Atribútmi:</p>
<ul>
<li>názvom miestnosti, v ktorej bola rezervácia uskutočnená <strong>room_name</strong> (<code>std::string</code>),</li>
<li>kód predmetu, pre ktorý bola rezervácia uskutočnená <strong>course_code</strong> (<code>std::string</code>),</li>
<li>začiatkom rezervácie <strong>start_time</strong> (<code>int</code>),</li>
<li>koncom rezervácie <strong>end_time</strong> (<code>int</code>).</li>
</ul>
<p>Metódy:</p>
<ul>
<li><code>void print()</code>, ktorá vypíše info o rezervácii a to vo formáte: <code>Reservation for Course &lt;course_code&gt; in Room &lt;room_name&gt; [&lt;start_time&gt;-&lt;end_time&gt;]\n</code></li>
</ul>
<p>Navyše, inštancia triedy Reservation sa musí dať vytvoriť nasledovne: <code>Reservation reservation(room_name, course_code, start_time, end_time);</code></p>
<h3 id="reservationsystem">ReservationSystem</h3>
<p>Trieda <code>ReservationSystem</code> predstavuje náš rezervačný systém, ktorý poskytuje služby pridávania miestností a kurzov, a následného rezervovania miestností pre dané kurzy. Túto funkcionalitu bude poskytovať tak, že si bude držat (privátny) register <a href="https://en.cppreference.com/w/cpp/container/vector">(<code>std::vector</code>)</a> všetkých miestností, kurzov a rezervácii, a poskytovať metódy nad nimi.</p>
<p>Verejné metódy ( Pozor! následné deklarácie sú len ukážkové - neobsahujú <code>const</code> a referencie) :</p>
<ul>
<li><p><code>bool addRoom(std::string name)</code> pridá na koniec zoznamu miestností novú miestnosť s názvom <em>name</em> , pokiaľ v zozname ešte nie je. Metóda vráti <code>true</code> práve vtedy keď bola miestnosť pridaná, <code>false</code> v prípade neúspechu.</p></li>
<li><p><code>bool hasRoom(std::string name)</code> vráti <code>true</code> ak register obsahuje miestnosť s menom <code>name</code>.</p></li>
<li><p><code>Room getRoom(std::string name)</code> na podobnom princípe ako <code>hasRoom</code>, avšak miesto logickej hodnoty vráti <strong>bezpečne</strong> (t.j. nemodifikovateľnú) a <strong>bez kopírovania</strong> inštanciu miestnosti s daným menom <code>name</code>. Takáto metóda bude volaná len ak daná miestnosť existuje - pokiaľ to tak nebude, zavolajte <code>throw std::runtime_error(&quot;Room not found.&quot;);</code>, t.j. vyvolajte <a href="https://en.cppreference.com/w/cpp/error/runtime_error">std::runtime_error</a>.</p></li>
<li><p><code>bool addCourse(std::string code, std::string teacher)</code> ako <code>addRoom</code> ale pridá nový kurz.</p></li>
<li><p><code>bool hasCourse(std::string code)</code> obdoba k <code>hasRoom</code> pre kurzy.</p></li>
<li><p><code>Course getCourse(std::string code)</code> obdoba k <code>getRoom</code> pre kurzy, v prípade že kurz neexistuje, zavolajte <code>throw std::runtime_error(&quot;Course not found.&quot;);</code>, t.j. vyvolajte <a href="https://en.cppreference.com/w/cpp/error/runtime_error">std::runtime_error</a>.</p></li>
<li><code>std::vector&lt;Room&gt; getRooms()</code>: <strong>bezpečne</strong> (t.j. nejde mimo túto metódu modifikovať) a <strong>bez kopírovania</strong> vráti uložený vektor miestností.</li>
<li><code>std::vector&lt;Course&gt; getCourses()</code>: to isté pre kurzy</li>
<li><p><code>std::vector&lt;Reservation&gt; getReservations()</code>: to isté pre rezervácie</p></li>
<li><p><code>bool makeAnyReservation(std::string course_code, int duration)</code> pokúsi sa vytvoriť v ľubovoľnej miestnosti rezerváciu dĺžky <code>duration</code> pre kurz s kódom <code>course_code</code>. Kurz <code>course_code</code> už musí existovať.</p></li>
<li><p><code>bool makeReservation(std::string course_code, std::string room_name, int from, int to)</code> pokúsi sa vytvoriť v miestnosti s názvom <code>room_name</code> rezerváciu od <code>from</code> do <code>to</code> pre kurz s kódom <code>course_code</code>. Kurz <code>course_code</code> a miesnosť <code>room_name</code> už musia existovať.</p></li>
</ul>
<p>Pre obe metódy platí: Výsledkom je <code>true</code> ak bola rezervácia úspešná, <code>false</code> ak nie. Neúspešnou je aj rezervácia, ktorá má niektorý zo vstupov nekorektný. V prípade úspešnej rezervácie bude vygenerovaná inštancia <code>Reservation</code>, ktorej atribúty budú naplnené podla definície triedy <code>Reservation</code>. Táto inštancia bude vložená <strong>na koniec</strong> registra rezervácii.</p>
<p>Navyše, inštancia triedy ReservationSystem sa musí dať vytvoriť nasledovne: <code>ReservationSystem rsystem;</code></p>
<h3 id="trieda-handler">Trieda <code>Handler</code></h3>
<p>Trieda <code>Handler</code> pokytuje verejné rozhranie pre užívateľa pre triedu <code>ReservationSystem</code>. To znamená, že interne si drží inštanciu triedy <code>ReservationSystem</code> a pomocou štandardného vstupu a výstupu komunikuje s uživateľom a vyvoláva metódy nad svojou inštanciou <code>ReservationSystem</code>.</p>
<p>Handler sa spustí zavolaním metódy <code>void handle()</code>.</p>
<p>Princíp komunikácie je nasledovný:</p>
<p>Zavolaním metódy <code>handle</code> sa spustí hlavný (potenciálne nekonečný) cyklus ktorý:</p>
<ol type="1">
<li><p>vypíše dostupné akcie (formát je na vás, ale výpis musí byť vždy rovnaký a ukončený znakom nového riadku)</p></li>
<li><p>zo štandardného vstupu načíta jedno číslo, ktoré bude odpovedať akcii z listu dostupných akcií.</p></li>
<li><p>Ak dané číslo neodpovedá žiadnej akcii prípadne ak počas vykonávania akcie nastane chyba, vypíšte na samostatný riadok na <strong>chybový výstup</strong> hlášku a pokračujte v hlavnom cykle.</p></li>
<li><p>Ak číslo odpovedá akcii, vykonajte akciu. Akcia môže pozostávať z dodatočného načítavania parametrov.</p></li>
</ol>
<p>Pre všetky reťazcové parametre platí, že budú zadávané až do konca nového riadku - odporúčame <a href="http://en.cppreference.com/w/cpp/string/basic_string/getline">getline</a>. Prázdny reťazec je považovaný za neplatný vstup a teda v prípade prázdneho reťazca vypíšte na chybový výstup informáciu o zlom vstupe a načítaj vstup znova (s výnimkou mena učiteľa - ten môže byť prázdny).</p>
<p>Pre číselné parametre platí, že po ich načítaní môžete všetko až do konca nového riadku ignorovať (t.j. po načítaní môžete použit <code>getline</code> pre dočítanie riadku, prípadne <a href="https://en.cppreference.com/w/cpp/io/basic_istream/ignore">std::cin::ignore</a>).</p>
<p>Pri operáciach výberu <em>áno/nie</em> vypíšte ľubovoľnú hlášku na štandardný vstup a očakávajte odpoveď vo formáte <code>yes</code>/<code>no</code>. Pri zadaní nekorektnej odpovede vypíšte na chybový výstup informáciu o zlom vstupe a postup opakujte, dokým nebude vstup korektný.</p>
<p>Pre číselné/reťazcové vstupy môžete predpokladať vstup v správnom formáte: ak požiadate o číslo, dostanete číslo, obdobne s reťazcom.</p>
<ol start="5" type="1">
<li>Ak spustená akcia dobehla úspešne, vypíšte <code>OK\n</code> na <strong>samostatný riadok</strong>. Je dôležité, aby ste túto hlášku vypísali vždy len <strong>práve raz</strong> pre každú úspešnú akciu (a teda ju nevypisujte napríklad po načítaní parametrov).</li>
</ol>
<p>Nevypisujte nič na chybový výstup, pokiaľ sa akcia podarila. Chybový výstup používajte vždy len na ohlásenie <strong>chyby</strong>.</p>
<p>Vždy, keď načítavate parameter zo štandardného vstupu, informujte uživateľa, čo chcete načítať. Toto upozornenie vždy ukončite znakom nového riadku!</p>
<p><strong>Príklad</strong></p>
<p><code>Zadaj meno:\n</code></p>
<p><code>Zadaj akciu:\n</code></p>
<p>Ak vám nebude určité chovanie zrejmé, overte ho najprv so <strong>vzorovým riešením</strong>, až následne píšte do diskusného fóra.</p>
<h4 id="akcie">Akcie</h4>
<ul>
<li><strong>0:</strong> Ukonči handler.</li>
<li><strong>1:</strong> Pridaj miestnosť – načítaj <em>meno</em> miestnosti a pridaj miestnosť do registra. Ak už taká miestnosť existuje, vypíš chybu.</li>
<li><strong>2:</strong> Pridaj kurz – načítaj kód <em>kurzu</em>, načítaj meno učiteľa (tu prázdny reťazec znamená, že kurz nemá učiteľa) a pridaj kurz. Ak už taký kurz existuje, vypíš chybu.</li>
<li><strong>3:</strong> Pridaj rezerváciu – načítaj kód kurzu. Následne sa spýtaj uživateľa, či si žiada pridať rezerváciu len na základe trvania - <em>áno/nie</em> operácia. Ak áno, načítaj trvanie a vytvor rezerváciu. Ak nie, tak načítaj názov miestnosti a interval od-do a vykonaj rezerváciu. Ak sa nepodarila, je akcia považovaná za chybnú. Akciu vyhláste za chybnú vždy až po načítaní všetkých potrebných parametrov.</li>
<li><strong>4:</strong> Vypíš všetky miestnosti – v poradí, v akom sú vo vektore.</li>
<li><strong>5:</strong> Vypíš všetky kurzy – v poradí, v akom sú vo vektore.</li>
<li><strong>6:</strong> Vypíš všetky rezervácie – v poradí, v akom sú vo vektore.</li>
<li><strong>7:</strong> Vypíš obsadenosť miestnosti - načíta meno miestnosti a vypíše jej aktuálnu obsadenosť (metóda <code>schedule</code>). Ak daná miestnoť neexistuje, akcia je považovaná za chybnú.</li>
</ul>
<h3 id="dodatočné-upozornenie">Dodatočné upozornenie:</h3>
<p>Pri rezervovaní miestnosti si dajte pozor, aby ste rezerváciu uskutočňovali nad miestnosťou vo vašom registri registrácii, a nie nad jej kópiou.</p>
<p><em>Príklad:</em> nech <code>rooms</code> je register miestnotí..</p>
<div class="sourceCode" id="cb1"><pre class="sourceCode .cpp"><code class="sourceCode cpp"><a class="sourceLine" id="cb1-1" data-line-number="1">rooms[<span class="dv">0</span>].occupy(...) - OK</a>
<a class="sourceLine" id="cb1-2" data-line-number="2">Room &amp;room = rooms[<span class="dv">0</span>]; room.occupy(...) - OK</a>
<a class="sourceLine" id="cb1-3" data-line-number="3">Room room = rooms[<span class="dv">0</span>]; room.occupy(...) - ZLE</a></code></pre></div>
<p>V posledom prípade vytvoríte <strong>kópiu</strong> vašej miestnosti z registra, a rezerváciu vytvoríte v kópii, nie v pôvodnej miestnosti. Dajte si pozor aj pri prechádzaní registra pomocou for-loopu. Rozlišujte, kedy kopírujete objekt (príklad označený ako zlý), a kedy len beriete referenciu na už existujúci objekt.</p>
<h3 id="vzorové-riešenie">Vzorové riešenie</h3>
<p>Vzorové riešenie je k dispozícii na Aise: <code>/home/xkejstov/hw01</code></p>
  </div>
  <div id="date">poslední změna: 2018-09-30 21:10</div>

