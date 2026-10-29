
---

## Study Map — خريطة المحاضرة

| Part | Topic |
| ---- | ----- |
\| 1 \| [[#Part 1 — Introduction to Embedded C\|Embedded C & Toolchain]]
\| 2 \| [[#Part 2 — Data Types & Memory Sizes\|Data Types & Memory Sizes]]
\| 3 \| [[#Part 3 — Variables, Casting & Conversion Pitfalls\|Variables, Casting & Conversion Problems]]
\| 4 \| [[#Part 4 — Modifiers, Qualifiers, Storage & Literals\|Type Modifiers, Qualifiers, Storage Classes & Literals]]
\| 5 \| [[#Part 5 — Embedded Memory Layout\|Memory Layout: Flash, RAM, Stack, Heap]]
\| 6 \| [[#Part 6 — Lab 1\|Lab 1 Tasks]]
\| 7 \| [[#Part 7 — Operators in C\|C Operators, Bitwise & Precedence]]
\| 8 \| [[#Part 8 — Decision Making & Switch\|Decision Making & Switch]]
\| 9 \| [[#Part 9 — Loops & Flow Control\|Loops & Flow Control]]
\| 10 \| [[#Part 10 — `goto` in C\|`goto` & Why to Avoid It]]

---

## Part 1 — Introduction to Embedded C

### What Is Embedded C?

- **Course title:** **Embedded C — Exploring the Embedded Programming**.
- الـ **⁦Embedded System⁩** هو جهاز فيه ⁦processor⁩ أو ⁦microcontroller⁩ مخصص لتنفيذ وظيفة محددة أو مجموعة وظائف محددة؛ زي ⁦washing machine⁩، ⁦smart sensor⁩، ⁦car controller.⁩
- الـ **⁦Embedded C⁩** هي ⁦C⁩ مستخدمة لبرمجة الأجهزة دي، وبتتعامل مع ⁦hardware resources⁩ اللي غالبًا بتكون محدودة.

**Big picture:**

```text
C Source Code → Build Tools → Firmware → Microcontroller → Hardware Action
```

يعني بنكتب تعليمات ⁦C⁩، نترجمها لـ⁦machine instructions⁩، ونحمّلها على المتحكم علشان يقرأ ⁦sensor⁩ أو يتحكم في ⁦LED⁩ / ⁦motor⁩ / ⁦communication peripheral.⁩

### Role of Embedded C in Embedded Systems

Embedded C is a variation of standard C customized for programming microcontrollers and low-level hardware.

**Why use Embedded C?**

1. ‏**⁦Low-level hardware access⁩:** تقدر تقرأ وتكتب في **⁦registers⁩**, **⁦ports⁩**, و**⁦pins⁩** مباشرة أو باستخدام ⁦drivers.⁩
2. ‏**⁦Fast⁩ & ⁦efficient⁩:** مناسبة لأجهزة ⁦RAM⁩ و⁦Flash⁩ بتاعتها صغيرة؛ مثال المحاضرة: جهاز فيه **2 ⁦KB RAM⁩**.
3. ‏**⁦Widely supported⁩:** منتشرة مع عائلات زي **⁦STM32⁩**, **⁦AVR⁩**, **⁦PIC⁩**.

**تفسير مهم:** أغلب ⁦Embedded C⁩ هي لغة ⁦C⁩ نفسها، لكن بنضيف عليها ⁦hardware-specific headers⁩، ⁦compiler extensions⁩ أحيانًا، وطرق الوصول لـ ⁦registers.⁩ مثلًا `PORTA` في ⁦AVR⁩ مرتبط بهاردوير معين؛ مش ⁦standard C⁩ موجود على كل جهاز.

**Practical example — LED:**

```c
// Pseudocode (NOT a universal MCU register name)
configure_pin_as_output(LED_PIN);
while (1) {
    set_pin_high(LED_PIN);
    delay_ms(500);
    set_pin_low(LED_PIN);
    delay_ms(500);
}
```

ده توضيح للفكرة، مش كود جاهز لكل ⁦Microcontroller.⁩ الدوال بتختلف حسب الـ ⁦MCU⁩ والـ ⁦SDK.⁩

> [!tip] Remember
> الـ **⁦PC application⁩** غالبًا بيطلب ⁦services⁩ من ⁦OS⁩؛ الـ **⁦bare-metal firmware⁩** يقدر يتحكم في ⁦hardware registers⁩ بشكل مباشر.


### C for PC vs Embedded C

| Feature | C for PC | Embedded C |
|---|---|---|
| **Platform** | General-purpose OS زي Windows / Linux | **Bare-metal** أو **RTOS** على MCU |
| **I/O** | `stdin`, `stdout`, files | `GPIO`, `UART`, `ADC`, إلخ |
| **Memory** | RAM وstorage غالبًا أكبر | RAM/Flash محدودين جدًا |
| **Execution model** | OS processes, threads, system calls | Firmware loop / tasks / interrupts |
| **Hardware access** | غالبًا OS-mediated | Direct registers أو low-level drivers |
| **Use cases** | Apps, games, scripts, websites | Sensors, control, real-time devices |

**مصطلحات لازم تبقى واضحة:**

- ‏**⁦Bare-metal⁩:** البرنامج شغال من غير ⁦Operating System⁩ تقليدي؛ إنت مسؤول عن ⁦initialization⁩ والـ ⁦main loop⁩ والـ ⁦interrupts.⁩
- ‏**⁦RTOS⁩:** ⁦Real-Time Operating System⁩؛ نظام خفيف بيساعدك تدير ⁦tasks⁩ وتحدد ⁦timing⁩ و⁦priorities.⁩
- ‏**⁦GPIO⁩:** ⁦General Purpose Input/Output⁩، ⁦pins⁩ لقراءة أو إرسال ⁦digital signal.⁩
- ‏**⁦UART⁩:** وسيلة ⁦serial communication.⁩
- ‏**⁦ADC⁩:** ⁦Analog-to-Digital Converter⁩ يحوّل ⁦voltage analog⁩ لقيمة ⁦digital.⁩
- ‏**⁦Real-time⁩:** مش معناها «سريع جدًا» بس، معناها الاستجابة تحصل في **⁦deadline⁩** محدد.

‏**⁦Scenario⁩:** لما ⁦sensor⁩ يبعت ⁦signal⁩، ⁦firmware⁩ ممكن يستخدم ⁦Interrupt⁩ عشان يستجيب بسرعة بدل ما يفضل يسأل ⁦pin⁩ باستمرار.

### The Embedded Toolchain

الـ **⁦Toolchain⁩** مجموعة ⁦tools⁩ بتحول ⁦C source file⁩ إلى ⁦firmware⁩ قابل للتشغيل على ⁦MCU.⁩

| Tool | Its job | Examples in slide |
|---|---|---|
| **Editor / IDE** | كتابة وتنظيم الكود | VS Code, Eclipse, STM32CubeIDE |
| **Compiler** | ترجمة C لـ lower-level/machine-target code | `avr-gcc`, ARM GCC, MPLAB XC8 |
| **Assembler** | ترجمة Assembly لـ object code | GNU `as` |
| **Linker** | يجمع object files والـ libraries، ويحدد addresses | GNU `ld` |
| **Debugger** | breakpoints, single-step, variables inspection | Atmel Studio, Keil, GDB, OpenOCD |
| **Programmer / Flasher** | كتابة الـ firmware على MCU | USBasp, ST-Link, J-Link |

**Build pipeline:**

```text
main.c + drivers.c + headers
              |
              v
      Compiler / Assembler
              |
              v
        Object Files (.o)
              |
              v
    Linker + Linker Script
              |
              v
        ELF / Executable
              |
      objcopy if needed
              |
              v
        HEX / BIN File
              |
              v
       Programmer / Flash
              |
              v
         Microcontroller
```

- ‏**⁦Compile error⁩:** غلط أثناء ترجمة ⁦source⁩، زي ⁦syntax error.⁩
- ‏**⁦Linker error⁩:** استخدمت ⁦function⁩ موجود ليها ⁦declaration⁩ لكن الـ ⁦linker⁩ مش لاقي الـ ⁦definition.⁩
- ‏**⁦Runtime⁩ / ⁦logic bug⁩:** البرنامج اترجم ونزل على الجهاز لكن ⁦behavior⁩ غلط.
- ‏**⁦Debugging⁩** ممكن يتم بوسائل زي ⁦breakpoint⁩ أو ⁦watch⁩ أو ⁦UART log.⁩

**ليه ⁦Linker Script⁩ مهم؟** لأنه بيحدد ⁦Flash/RAM regions⁩ وأماكن ⁦sections⁩ زي `.text`, `.data`, `.bss`. دي نقطة هترجع تاني في **⁦Memory Layout⁩**.

---

## Part 2 — Data Types & Memory Sizes

### Classification of Data Types

**الـ ⁦Data Type⁩** بيحدد شكل البيانات، عملياتها الممكنة، وحجم الـ ⁦storage⁩ المتوقع.

**تصنيف السلايد:**

```text
Data Types in C
├── Primary / Basic
│   ├── int
│   ├── char
│   ├── float
│   └── double
├── Derived
│   ├── Arrays
│   ├── Pointers
│   └── Functions
└── User-defined
    ├── struct
    ├── union
    └── enum (enumeration)
```

**الفرق:**

‏- `char`: ⁦integer type⁩ صغير، غالبًا بنستخدمه مع ⁦characters⁩ أو ⁦bytes.⁩
‏- `int`: integer values.
‏-`float`, `double`: أرقام فيها ⁦fractional part.

⁩
- ‏**⁦Array⁩:** عناصر من نفس النوع جنب بعض منطقيًا في الذاكرة.
- ‏**⁦Pointer⁩:** يحتفظ بـ ⁦address⁩ لمكان في الذاكرة.
- ‏**⁦Function⁩:** كود قابل لإعادة الاستخدام.
- ‏**⁦struct⁩:** تجمع ⁦fields⁩ مختلفة، كل ⁦field⁩ ليه ⁦storage.⁩
- ‏**⁦union⁩:** أعضاء بيشاركوا نفس ⁦storage⁩؛ الحجم عادة يكفي أكبر ⁦member⁩ مع ⁦alignment.⁩
- ‏**⁦Enum⁩:** أسماء رمزية لقيم ⁦integer⁩، زي `RED`, `GREEN`, `BLUE`.

```c
int counter = 10;
char letter = 'A';
float temperature = 25.5f;
int readings[3] = {100, 200, 300};

struct Sensor {
    int id;
    float reading;
};
```

‏**⁦Embedded relevance⁩:** لو عندك 2 ⁦KB RAM⁩، اختيار ⁦buffer⁩ من 1000 عنصر `uint32_t` بدل `uint8_t` ممكن يخلي البرنامج مش قادر يتحمل الاستهلاك.

### Integer Types: Storage Size & Value Range

السلايد بتعرض جدول الأحجام والمديات الآتية (كأمثلة منصات/⁦implementations⁩):

| Type             | Size                  | Range                                        |
| ---------------- | --------------------- | -------------------------------------------- |
| `char`           | 1 byte                | −128..127 **or** 0..255                      |
| `unsigned char`  | 1 byte                | 0..255                                       |
| `signed char`    | 1 byte                | −128..127                                    |
| `int`            | 2 or 4 bytes          | −32768..32767 **or** −2147483648..2147483647 |
| `unsigned int`   | 2 or 4 bytes          | 0..65535 **or** 0..4294967295                |
| `short`          | 2 bytes               | −32768..32767                                |
| `unsigned short` | 2 bytes               | 0..65535                                     |
| `long`           | 8 bytes (as depicted) | −9223372036854775808..9223372036854775807    |
| `unsigned long`  | 8 bytes (as depicted) | 0..18446744073709551615                      |

**الفكرة وراء ⁦ranges⁩:**

- 8-⁦bit unsigned⁩: من `0` لـ `2^8 - 1 = 255`.
- 8-⁦bit signed⁩ (⁦two⁩'⁦s complement⁩ المعتاد): من `-2^7 = -128` لـ `2^7 - 1 = 127`.
- 16-bit unsigned: `0..65535`.
- 16-bit signed: `-32768..32767`.

> [!warning] Important clarification — don't memorize every size as universal
> ‏جدول السلايد بيعرض ⁦sizes⁩ محددة، لكن **⁦C standard⁩ لا يضمن إن `int` = 4 ⁦bytes⁩ أو `long` = 8 ⁦bytes⁩** على كل جهاز. في كثير من ⁦AVR toolchains⁩ الـ `int` بيكون 16-⁦bit⁩ و`long` غالبًا 32-⁦bit⁩، وعلى منصات تانية تختلف الأحجام. كمان **`char` دائمًا 1 ⁦C byte⁩** لكن عدد الـ ⁦bits⁩ في ⁦byte⁩ بيتحدد بـ `CHAR_BIT`. للحجم الدقيق استعمل `sizeof` و`<limits.h>`، ولحجم ثابت نسبيًا استخدم `uint8_t`, `uint16_t`, `uint32_t` من `<stdint.h>` حيث تتوفر.

**Signed vs unsigned:**

```c
#include <stdint.h>
uint8_t  a = 250;  // 0..255
int8_t   b = -6;   // -128..127
uint16_t c = 5000; // 0..65535
```

- استخدم `unsigned` لما المجال غير سالب ويهمك ⁦full positive range⁩، لكن خليك حذر في ⁦subtraction⁩ و⁦comparison.⁩
- استخدم **⁦fixed-width types⁩** في ⁦protocols⁩, ⁦peripheral registers⁩, ⁦binary buffers.⁩

### `<limits.h>` & Checking Integer Limits

السلايد فيها برنامج بيستخدم `<stdio.h>` و`<limits.h>` عشان يطبع الحدود المتاحة على الـ ⁦compiler⁩ الحالي، مثل:

- `CHAR_BIT`: عدد الـ⁦bits⁩ في الـ⁦byte.⁩
- `CHAR_MIN`, `CHAR_MAX`: ⁦range⁩ الـ`char`.
- `INT_MIN`, `INT_MAX`: ⁦range⁩ الـ`int`.
- `LONG_MIN`, `LONG_MAX`: ⁦range⁩ الـ`long`.
- `SCHAR_MIN`, `SCHAR_MAX`: ⁦range⁩ الـ`signed char`.
- `SHRT_MIN`, `SHRT_MAX`: ⁦range⁩ الـ`short`.
- `UCHAR_MAX`, `UINT_MAX`, `ULONG_MAX`, `USHRT_MAX`: ⁦maximum⁩ للأنواع ⁦unsigned.⁩

**Simplified runnable example:**

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("CHAR_BIT = %d\n", CHAR_BIT);
    printf("INT_MIN  = %d\n", INT_MIN);
    printf("INT_MAX  = %d\n", INT_MAX);
    printf("UINT_MAX = %u\n", UINT_MAX);
    printf("Size of int = %zu bytes\n", sizeof(int));
    return 0;
}
```

**يعني إيه ⁦Macro⁩؟** `INT_MAX` مش ⁦variable⁩، ده ⁦constant-like macro⁩ معرفة في الـ ⁦header⁩، بتتحدد حسب ⁦compiler/platform.⁩

> [!tip] Exam / Interview
> سؤال: `sizeof(int)` كام؟ الإجابة الصح: **⁦implementation-dependent⁩**؛ لازم أعرف الـ ⁦target/compiler⁩، مش أحفظ رقم ثابت.

###  Floating-Point Types / Precision / `<float.h>`

**الجدول اللي في السلايد:**

| Type | Size shown | Approximate range shown | Approximate decimal precision |
|---|---|---|---|
| `float` | 4 bytes | `1.2e−38` to `3.4e38` | ~6 digits |
| `double` | 8 bytes | `2.3e−308` to `1.7e308` | ~15 digits |
| `long double` | 10 bytes | `3.4e−4932` to `1.1e4932` | ~19 digits |

 بتستخدم `<float.h>` عشان تعرض `FLT_MAX`, `FLT_MIN`, `DBL_MAX`, `DBL_MIN`, `FLT_DIG` إلخ.

```c
#include <stdio.h>
#include <float.h>

int main(void) {
    printf("float bytes: %zu\n", sizeof(float));
    printf("FLT_MAX: %e\n", (double)FLT_MAX);
    printf("FLT_MIN: %e\n", (double)FLT_MIN);
    printf("FLT_DIG: %d\n", FLT_DIG);
    return 0;
}
```

**Precision vs range:**

- ‏**⁦Range⁩**: أكبر وأصغر ⁦magnitude⁩ النوع يقدر يمثّلها.
- ‏**⁦Precision⁩**: قد إيه يقدر يحتفظ بـ ⁦meaningful significant digits.⁩
- `float` غالبًا 32-⁦bit IEEE⁩ 754، لكن التفاصيل مش ⁦guaranteed⁩ على كل ⁦MCU.⁩
- `double` و`long double` ممكن يختلفوا عن جدول السلايد على منصات ⁦Embedded.⁩

‏**⁦Example⁩:** `0.1f + 0.2f` ممكن ما يساويش `0.3f` بالضبط بسبب ⁦binary floating-point rounding.⁩

‏**⁦Embedded relevance⁩:** الحسابات العائمة بتستهلك ⁦CPU/time/flash⁩ زيادة في ⁦MCU⁩ من غير **⁦FPU⁩** (⁦Floating-Point Unit⁩). لو محتاج حسابات مالية أو ⁦sensor scale⁩ ثابتة ممكن تستخدم **⁦fixed-point integers⁩** بدل ⁦float⁩ في بعض الحالات.

> [!warning] Important clarification
> `FLT_MIN` هو **أصغر ⁦positive normalized float⁩**، مش «أكثر قيمة سالبة». القيم والأحجام المذكورة في السلايد ⁦examples⁩ وليست ⁦standards⁩ مضمونة للجميع.

---

## Part 3 — Variables, Casting & Conversion Pitfalls

###  Variable Declaration vs Definition

**صياغة السلايد:**

- ‏**⁦Declaration⁩:** بتقول للـ ⁦compiler⁩ إن ⁦variable⁩ موجودة ⁦somewhere.⁩
- ‏**⁦Definition⁩:** بتعمل ⁦storage⁩ للـ ⁦variable⁩، غالبًا بتهيئ الذاكرة حسب النوع والسياق.
- **Rule of thumb:** `Declaration = Promise` / `Definition = Creation`.

```c
extern int speed;   // Declaration only (no definition here)
int speed = 100;    // Definition (and initialization)
```

**التفصيل:**

- ‏⁦Declaration⁩ بتعرّف الاسم والـ ⁦type⁩ للـ ⁦compiler⁩ عشان يعرف يستخدمه.
- ‏⁦Definition⁩ بتوفر الـ ⁦object⁩ فعلًا في ⁦program.⁩
- في ⁦C⁩، ⁦statement⁩ زي `int x;` على ⁦file scope⁩ عادة **⁦tentative definition⁩**؛ مش مجرد وعد زي `extern int x;`.
- **الـ ⁦definition⁩ الواحدة** مطلوبة للـ ⁦external object⁩ على مستوى البرنامج النهائي؛ لكن ⁦declaration⁩ تقدر تتكرر بشكل ⁦compatible.⁩

```c
// sensor.h
extern int sensor_value;

// sensor.c
int sensor_value = 25;

// main.c
#include "sensor.h"
// use sensor_value
```

هنا ⁦header⁩ ما بيعملش ⁦duplicate definitions⁩؛ بيدّي ⁦declaration⁩ لكل ⁦file.⁩

### `extern`, Local & Global Variables

**`extern`:** كلمة بتقول إن تعريف ⁦global variable⁩ موجود في مكان تاني، وبتستخدمها مع ⁦multiple⁩ `.c` ⁦files.⁩

| Feature | Local variable | Global variable |
|---|---|---|
| Place | جوه function أو block | خارج كل functions |
| Scope | visible within block | visible where declared; يمكن عبر files مع declaration صحيح |
| Lifetime (usual case) | خلال execution of block/function | طول فترة تشغيل البرنامج |
| Memory (typical) | Stack، أو register optimized | `.data` / `.bss` |

```c
int total_events = 0;  // Global

void on_event(void) {
    int local_count = 1;   // Local automatic
    total_events += local_count;
}
```

**Scope ≠ Lifetime:**

- ‏**⁦Scope⁩:** أقدر أستخدم الاسم فين؟
- ‏**⁦Lifetime⁩ / ⁦Storage duration⁩:** الـ ⁦object⁩ نفسه عايش قد إيه؟
- ‏⁦Local⁩ `static` ⁦variable⁩ اسمها ⁦local⁩ لكن ⁦lifetime⁩ طول تشغيل البرنامج (هنتكلم عنها في ⁦Slide⁩ 19 و25).

> [!warning] Important clarification
> جملة «⁦local variables are stored on the stack⁩» هي **الصورة الشائعة**، لكن ⁦compiler⁩ ممكن يخزن متغير في ⁦register⁩ أو يعمل ⁦optimization⁩ من غير ⁦storage⁩ فعلية. وجود ⁦global⁩ في ⁦file⁩ مش معناه تلقائيًا إنها ⁦visible⁩ في كل الملفات؛ ⁦linkage/declaration⁩ مهمين.

###  Implicit vs Explicit Type Casting

‏**⁦Implicit conversion⁩** = ⁦compiler⁩ بيحوّل النوع ⁦automatically⁩ حسب ⁦language rules.⁩

```c
int x = 5;
float y = x;          // int → float automatically
int result = 5 + 'A'; // char participates in integer promotions
```

‏**⁦Explicit cast⁩** = أنت بتطلب ⁦conversion⁩ بنفسك:

```c
float a = 7.9f;
int b = (int)a;       // b becomes 7, fractional part removed
```

**Syntax:** `(new_type) expression`.

**ليه ده مهم؟** لأن ⁦conversion⁩ ممكن يعمل:

1. ‏**⁦Loss of precision⁩** (خصوصًا ⁦float⁩ ↔ ⁦int⁩).
2. ‏**⁦Truncation⁩** لما القيمة لا تناسب الـ ⁦destination.⁩
3. ‏**⁦Sign mismatch⁩** بين ⁦signed/unsigned.⁩
4. ‏⁦Arithmetic⁩ مختلف عن اللي توقعته.

```c
int a = 5, b = 2;
float x = a / b;        // 2.0  (integer division first!)
float y = (float)a / b; // 2.5  (floating division)
```

> [!tip] Key rule
> مكان الـ **⁦cast⁩** مهم. لو حسبت ⁦integer division⁩ الأول، تخزين النتيجة في `float` مش هيرجع الكسور اللي ضاعت.

###  Type Conversion Mismatch: Truncation

السلايد بتشرح إن نقل قيمة من ⁦type⁩ كبير أو ⁦wide⁩ إلى ⁦type⁩ أضيق ممكن يفقد ⁦bits.⁩

**Example in slide:**

```c
int x = 300;
char y = (char)x;
```

**Binary:**

```text
300 decimal = 00000001 00101100 (16-bit illustration)
Low 8 bits =          00101100 = 44 decimal
```

لو ⁦destination effectively⁩ 8-⁦bit⁩، الجزء الأعلى `00000001` ضاع، وبالتالي ⁦low byte⁩ بقى `44`.

**What's happening?**

1. `int` يقدر يشيل `300` على الأنظمة المقصودة.
2. بنحوّل إلى ⁦narrow⁩ `char`.
3. قيمة الـ ⁦destination⁩ لا تقدر تمثل `300` في 8-⁦bit.⁩
4. السلايد بتوضح ⁦low-byte truncation⁩ ⇒ `44`.

> [!warning] Important clarification
> المثال مضمون على 8-⁦bit⁩ **`unsigned char`** من حيث ⁦modulo⁩ `256`: `300 % 256 = 44`. مع ⁦plain⁩ `char` لو هي ⁦signed⁩ و`300` خارج المدى، النتيجة على ⁦C implementations⁩ قد تكون **⁦implementation-defined⁩**؛ لذلك الأفضل في الشرح الدقيق استخدام `uint8_t` أو `unsigned char` لما تقصد ⁦byte.⁩

###  Sign Mismatch (`uint8_t` → `int8_t`)

**Example in slide:**

```c
#include <stdint.h>
uint8_t a = 250;
int8_t b = (int8_t)a;
```

- `uint8_t` من `0..255`.
- `int8_t` من `−128..127`.
- `250` أكبر من الحد الموجب لـ ⁦signed⁩ 8-⁦bit.⁩
- السلايد بتعرض النتيجة الشائعة: `b = -6`.

‏**⁦Why⁩?** نفس ⁦pattern⁩ للـ ⁦bits⁩ بيتفسر ⁦signed two⁩'⁦s complement⁩ بدل ⁦unsigned.⁩

### Step-by-Step Two's Complement

```text
250 decimal = 11111010 (8 bits)
Top bit     = 1  → negative in 8-bit signed two's complement
Invert      = 00000101
Add 1       = 00000110
Magnitude   = 6
Signed val  = -6
```

**شرح:**

1. `250` في ⁦binary⁩ = `11111010`.
2. أول ⁦bit⁩ = `1`؛ عند تفسيره كـ `int8_t` في ⁦two⁩'⁦s complement⁩ ده ⁦sign negative.⁩
3. نقلب الـ ⁦bits⁩: `00000101`.
4. نزوّد `1` ⇒ `00000110` = `6`.
5. يبقى ⁦value⁩ = `−6`.

**مهم جدًا:** المثال بيعلمك **⁦bit interpretation⁩**؛ لو حولت قيمة خارج الـ⁦range⁩ إلى ⁦signed type⁩، ⁦C⁩ ما بيوعدكش دائمًا بنفس النتيجة على كل ⁦implementation⁩، حتى لو `-6` هي النتيجة المعتادة في أنظمة ⁦embedded⁩ الحديثة.

### Overflow

‏**⁦Overflow⁩:** لما نتيجة عملية حسابية تتجاوز ⁦maximum⁩ (أو ⁦minimum⁩) النوع.

**Example in slide:**

```c
#include <stdint.h>

uint8_t a = 200;
uint8_t b = 100;
uint8_t result = a + b; // 300 doesn't fit in 8 bits
// Result is 44 on the usual 8-bit uint8_t case
```

**السبب:** `300 % 256 = 44`، لأن الـ ⁦destination⁩ مداها `0..255`.

**Avoiding the problem:**

```c
#include <stdint.h>
uint8_t a = 200, b = 100;
uint16_t correct_result = (uint16_t)a + (uint16_t)b; // 300
```

**Very important detail:**

- العمليات على `uint8_t` غالبًا بتتعمل بعد **⁦integer promotions⁩** إلى `int` لو يقدر يحمل القيم؛ المشكلة في المثال بتحصل لما الـ `300` تتخزن في `uint8_t`.
- ‏**⁦Unsigned arithmetic⁩** بتتصرف ⁦modular⁩ حسب عرض النوع.
- ‏**⁦Signed integer overflow⁩** في ⁦C⁩ يعتبر **⁦undefined behavior⁩**؛ متفترضش إن النتيجة هتعمل ⁦wrap⁩ زي ⁦unsigned.⁩

‏**⁦Embedded impact⁩:** لو ⁦overflow⁩ حصل في ⁦timer counter⁩ / ⁦sensor measurement⁩ / ⁦packet length⁩، ده ممكن يغير ⁦behavior⁩ أو يسبب ⁦bug⁩ صعب تلاحظه.

---

## Part 4 — Modifiers, Qualifiers, Storage & Literals

### Type Modifiers

‏**⁦Modifiers⁩** بتغير ⁦range⁩ أو ⁦representation⁩ المتوقع من ⁦integer/floating type.⁩

| Modifier | Applies to / Usage | Idea |
|---|---|---|
| `short` | `short int` | integer type بمدى/حجم أصغر أو مساوي لـ int حسب المنصة |
| `long` | `long int`, `long double` | integer/float extension حسب النوع والـ compiler |
| `signed` | `signed int`, `signed char` | قيم سالبة وموجبة |
| `unsigned` | `unsigned int`, `unsigned char` | قيم غير سالبة |

```c
short int x = 100;
long int distance = 100000L;
signed char offset = -2;
unsigned int pulses = 500U;
```

‏**⁦Why use modifiers⁩?** تختار ⁦representable range⁩ وطريقة تفسير ⁦bits⁩ المطلوبة في برنامجك.

> [!warning] Important clarification
> `unsigned` مش معناه العدد «⁦positive only⁩» حرفيًا؛ **صفر كمان مسموح**. و`long` مش لازم يكون 64-⁦bit⁩؛ ارجع لجدول الـ ⁦target⁩ و`sizeof`.

### Type Qualifiers: `const` & `volatile`

**`const`** = من خلال الاسم ده، مش مسموح تعدل ⁦object⁩ بالطريقة المعتادة بعد ⁦initialization.⁩

```c
const int MAX_SPEED = 120;
// MAX_SPEED = 130;   // compile-time diagnostic
```

‏**⁦Why⁩?** تحمي ⁦values⁩ أو ⁦interface⁩ من التعديل الخطأ، زي ⁦calibration constant.⁩

**`volatile`** = بتقول للـ ⁦compiler⁩ إن القيمة ممكن تتغير بطريقة مش واضحة من تنفيذ الكود العادي؛ وبالتالي لازم يحافظ على ⁦accesses⁩ اللي اللغة بتعتبرها ⁦observable⁩، ومينفعش يفترض إنها ثابتة.

**Use cases from slide:**

- ‏**⁦Interrupt Service Routine⁩ (⁦ISR⁩)** تعدّل ⁦variable.⁩
- **Memory-mapped peripheral registers**.
- Hardware interface values.

```c
#include <stdint.h>

volatile uint8_t flag = 0;

void interrupt_handler(void) {
    flag = 1;
}

int main(void) {
    while (flag == 0) {
        // wait for hardware event
    }
    // Handle event
    return 0;
}
```

**لو شلت ⁦volatile⁩:** ⁦compiler⁩ ممكن يلاحظ إن `flag` ما اتغيرتش داخل ⁦loop⁩ نفسها، ويعمل ⁦optimization⁩ غير مناسبة لو التغير بيحصل خارج ⁦execution⁩ العادي.

**Memory-mapped example (illustrative):**

```c
#define GPIO_REGISTER (*(volatile uint32_t *)0x40020000u)
// Address illustrative only; NOT safe for arbitrary hardware
```

> [!warning] Important clarification
> `volatile` **مش** ⁦Mutex⁩ / ⁦atomic⁩ / ⁦synchronization primitive⁩؛ ما بيحلّش ⁦race conditions⁩ لوحده، ومش بيمنع كل ⁦optimizations.⁩ و`const` **مش ضمان** إن ⁦object⁩ هيتحط في ⁦Flash⁩؛ مكان التخزين بيتحدد حسب ⁦platform⁩, ⁦compiler⁩, ⁦linker⁩ و⁦usage.⁩

**`const volatile` مع بعض؟** ممكن جدًا: ⁦hardware status register⁩ بنقرأها ومش بنكتب فيها من خلال ⁦pointer⁩ ده، لكن ⁦hardware⁩ نفسه يغيّر قيمتها.

### Storage Classes: `auto`, `static`, `register`, `extern`

| Keyword | Scope/Use | Lifetime | Main idea |
|---|---|---|---|
| `auto` | Local variable | خلال block execution | automatic storage default |
| `static` local | Inside function | طوال program | يحتفظ بقيمته بين calls |
| `static` file-scope | Outside functions | طوال program | يقيّد visibility إلى translation unit |
| `register` | Local | automatic | hint قديم للcompiler لتخزين سريع |
| `extern` | Declaration للـ external object | حسب object الفعلي | الوصول إلى global مُعرّف elsewhere |

**`auto` example:**

```c
void work(void) {
    auto int temp = 5; // same general behavior as: int temp = 5;
}
```

**`static` local example:**

```c
int next_id(void) {
    static int id = 0;
    id++;
    return id;
}
// calls yield 1, then 2, then 3...
```

**`static` global example:**

```c
static int private_counter = 0; // accessible by name only in this .c unit
```

**`extern` example:**

```c
extern int shared_counter; // storage defined in another source file
```

> [!tip] Distinguish
> `static` داخل ⁦function⁩ = ⁦local⁩ **⁦scope⁩** لكن ⁦static⁩ **⁦lifetime⁩**. `static` بره ⁦function⁩ = ⁦static lifetime⁩ **⁦plus internal linkage⁩** (الاسم مش ⁦exposed⁩ لباقي ⁦C files⁩).

**`register`:** مجرد ⁦hint⁩ تاريخيًا، ومفيش ضمان إنه يتحط في ⁦CPU register.⁩ حسب ⁦C rules⁩ الكلاسيكية، ممنوع تاخد ⁦address⁩ لمتغير معلن `register` باستخدام `&`.

### Literals in C

‏**⁦Literal⁩** = قيمة مكتوبة داخل الكود مباشرة، مش قيمة ⁦variable.⁩

| Literal type | Format / suffix | Example | Meaning |
|---|---|---|---|
| Decimal integer | digits | `100` | Base 10 |
| Unsigned integer | `U` / `u` | `100U` | Unsigned |
| Long integer | `L` / `l` | `1000L` | Long |
| Unsigned long | `UL` / `ul` | `1000UL` | Unsigned long |
| Octal | leading `0` | `075` | Base 8 ⇒ decimal 61 |
| Hexadecimal | `0x` / `0X` | `0xFFU` | Base 16 ⇒ 255 |
| Float literal | suffix `f` / `F` | `3.14f` | `float` |
| Long double | suffix `L` | `2.0L` | `long double` |
| Exponential | `e`/`E` | `1.5e3f` | `1500.0f` |
| Character | single quotes | `'A'` | character constant |
| String | double quotes | `"Hello"` | string literal |

**انتبه للأصفار:**

```c
int a = 10;   // decimal 10
int b = 010;  // octal 10 = decimal 8
int c = 0x10; // hex 10 = decimal 16
```

**Characters vs strings:**

```c
char letter = 'A';       // single character
const char *s = "A";    // a string: 'A' then '\0'
```

- `'A'` في ⁦C character constant⁩ من ⁦type⁩ `int` (على عكس ما ناس كتير متوقعة)، لكن ينفع نخزنها في `char` لو في ⁦range.⁩
- `"A"` عبارة عن ⁦array⁩ فيها `A` وبعدها ⁦null terminator⁩ `\0`.
- تقدر تستخدم ⁦hex literals⁩ كتير في ⁦registers⁩ والـ ⁦bit masks.⁩

---

## Part 5 — Embedded Memory Layout

### Memory Layout Overview

في السلايد رسم مقارنة بين **⁦Flash⁩** و**⁦RAM⁩**، وموضح ⁦sections⁩ كتير.

```text
FLASH / ROM (typical)              RAM (typical)
+---------------------+            +----------------------+
| .text  (program)    |            | Stack                |
+---------------------+            +----------------------+
| .rodata (constants) |            | Heap (if configured) |
+---------------------+            +----------------------+
| .data initializers  |  --copy--> | .data (initialized)  |
+---------------------+            +----------------------+
| Vector Table        |            | .bss  (zeroed)       |
+---------------------+            +----------------------+
```

‏**⁦Why segmentation⁩?** لأن البيانات مش كلها زي بعض من ناحية:

- ‏**⁦Purpose⁩**: ⁦code⁩ ولا ⁦variable⁩ ولا ⁦interrupt vectors⁩؟
- ‏**⁦Lifetime⁩**: لحظة مؤقتة ولا طول البرنامج؟
- ‏**⁦Permission⁩**: ⁦read-only⁩ ولا ⁦writable⁩؟
- ‏**⁦Storage device⁩**: ⁦Flash⁩ ولا ⁦RAM⁩؟

### Why Divide Memory into Segments?

**خمسة أسباب موجودة في السلايد:**

1. ‏**⁦Different lifetimes⁩:** ⁦global variables⁩ طول البرنامج، ⁦stack locals⁩ مؤقتة، ⁦heap objects⁩ لحد ما تتحرر، و⁦Flash⁩ يحتفظ بالبيانات بعد ⁦power-off.⁩
2. ‏**⁦Different writability⁩:** ⁦instructions/constants⁩ غالبًا ⁦read-only⁩؛ المتغيرات ⁦writable⁩ محتاجة ⁦RAM.⁩
3. ‏**⁦Different initialization⁩:** `int x = 5;` في ⁦global/static⁩ محتاج ⁦initial value⁩ محفوظة، وبعد الإقلاع تتجهز في ⁦RAM⁩؛ غير ⁦initialized globals⁩ بتتصفر.
4. ‏**⁦Different memory types/speeds⁩:** ⁦internal SRAM⁩, ⁦SDRAM⁩, ⁦Flash⁩, ⁦TCM⁩ ممكن تختلف في ⁦speed/size.⁩
5. ‏**⁦Tight resource constraints⁩:** ⁦RAM/Flash⁩ صغيرة، والـ ⁦linker⁩ بيحسب ⁦usage⁩ لكل ⁦section⁩ ويكشف ⁦section overflow.⁩

**What happens at reset? Simplified:**

```text
Power on / Reset
      ↓
CPU starts at reset handler
      ↓
Startup code prepares memory:
  - Copy initialized .data values from Flash to RAM
  - Zero .bss in RAM
      ↓
Runtime initialization (if any)
      ↓
main()
```

> [!tip] Why important for Embedded?
> ممكن الكود يترجم صح في ⁦C⁩، لكن الـ ⁦linker⁩ يدي ⁦Error⁩ إن `.bss` أو `.data` مش لاقية مكان كفاية في ⁦SRAM.⁩ ده معناه ⁦RAM usage⁩ أكبر من قدرة الـ ⁦target.⁩

### What's Stored in Flash?

| Flash section / region | Contains | Examples |
|---|---|---|
| `.text` | Machine instructions | Compiled C functions |
| `.rodata` | Read-only constant data | String literals, const tables, LUT |
| `.data` **initializers** | Starting values for mutable globals/statics | Initial `10` for `int x = 10` |
| **Vector Table** | Addresses/entries of reset & interrupts | Reset, Timer IRQ, UART IRQ |
| **Bootloader** (optional) | Startup/firmware update code | Firmware updater |
| **Configuration / Calibration** (optional) | Persistent device settings | Calibration coefficients |

‏**⁦Lookup Table⁩ (⁦LUT⁩):** مجموعة ⁦values⁩ محسوبة ومخزنة مسبقًا بدل حسابها كل مرة.

> [!tip] LUT Memory Location
> - **LUT** = Look-Up Table.
> - **ARM/STM32:** Constant LUT → typically `.rodata` in Flash.
> - **AVR/ATmega32:** Use `PROGMEM` to keep LUT in Flash.
> - **Modifiable Global LUT:** typically `.data` in RAM.
> - Actual placement depends on the Compiler and Linker Script.

```c
static const unsigned char pwm_table[] = {0, 10, 25, 45, 70, 100};
// Use pwm_table[index] instead of re-calculating a formula
```

‏**⁦Tradeoff⁩:** ⁦LUT⁩ تستهلك ⁦Flash/ROM⁩ أكتر لكن ممكن توفّر ⁦execution time⁩، وده مهم في ⁦low-power⁩ أو ⁦time-critical firmware.⁩

‏**⁦Interrupt Vector Table⁩:** المكان اللي ⁦processor⁩ بيرجعله عشان يعرف عنوان الـ ⁦handler⁩ المناسب عند ⁦reset⁩ أو ⁦IRQ.⁩


> [!important] Why is ROM Non-Volatile & Hard to Write?
> الـ **⁦Flash Memory⁩** بتستخدم ⁦Memory Cells⁩ مبنية غالبًا على **⁦Floating-Gate MOSFETs⁩** أو تقنيات مشابهة.
>
> - ‏**⁦Data Storage⁩:** البيانات بتتخزن على هيئة ⁦Electrical Charge⁩ داخل الـ ⁦Memory Cell.⁩
> - ‏**⁦Non-Volatile⁩:** الشحنة بتفضل محفوظة حتى بعد فصل الـ ⁦Power⁩، وبالتالي البيانات مش بتضيع.
> - ‏**⁦Reading⁩:** قراءة البيانات ممكن تتم باستخدام الـ ⁦Normal Operating Voltage.⁩
> - ‏**⁦Writing⁩ / ⁦Erasing⁩:** تغيير الشحنة بيحتاج **⁦Special Programming/Erasing Voltages⁩** أعلى من الجهد المستخدم للقراءة، مع دوائر تحكم خاصة.
> - ‏**⁦Charge Pump⁩:** في الـ ⁦Microcontrollers⁩ الحديثة، الجهد المطلوب غالبًا بيتولد داخليًا باستخدام ⁦Charge Pump Circuit.⁩
>
> **Key Idea:** Flash Memory can be reprogrammed, but writing requires special operations, unlike RAM.


### What's Stored in RAM?

| RAM section/region | Typical content | Why? |
|---|---|---|
| `.data` | Initialized global/static variables | Writable during runtime |
| `.bss` | Zero/uninitialized global/static variables | RAM for objects starting at zero |
| **Stack** | Call frames, local automatic vars, return info, saved registers | Temporary function execution |
| **Heap** (if used) | `malloc`, `calloc`, `realloc` allocations | Dynamic memory at runtime |
| **DMA buffers** (if used) | Data accessible to peripheral DMA | Transfer without CPU copying each byte |
| **Peripheral/shared buffers** | Communication or sensor data | Exchange between tasks / hardware |

**Examples:**

```c
int ready = 1;             // usually .data (writable)
int counter;               // usually .bss (starts as zero)
static int samples[100];   // usually .bss

void update(void) {
    int local = 10;        // typically stack/register
}
```

**Stack vs Heap:**

- ‏**⁦Stack⁩:** ⁦automatic allocation⁩ عند ⁦function calls⁩، ولازم تنتبه لـ ⁦deep recursion⁩ و⁦large local arrays.⁩
- ‏**⁦Heap⁩:** ⁦dynamic memory⁩، مفيدة أحيانًا لكن تسبب ⁦fragmentation⁩ أو ⁦unpredictable latency⁩، وده سبب إن بعض ⁦embedded projects⁩ تقلل استخدامها.
- ‏**⁦DMA buffers⁩:** مكانها الفعلي بيتحدد حسب ⁦linker⁩ و⁦memory map⁩ و⁦DMA controller requirements⁩؛ ممكن تحتاج ⁦alignment⁩ أو ⁦cache handling.⁩

> [!warning] Embedded detail
> مش كل ⁦MCU⁩ بيكون فيها ⁦Heap⁩ مفعّلة. والرسم في السلايد **⁦conceptual⁩**، مش عنوان ذاكرة ثابت ولا ترتيب واحد لكل ⁦microcontrollers.⁩

### Local, `const`, & `static` Example

السلايد فيها ⁦function⁩ اسمها `test_locals()`، بتعرّف ثلاث ⁦variables⁩:

1. `int local_var = 1;` — automatic local variable.
2. `const int const_local_var = 2;` — لا يجوز تعديلها عبر الاسم ده.
3. `static int static_local_var = 0;` — ⁦local scope⁩ لكن القيمة تستمر بين ⁦calls.⁩

**Code corresponding to the slide:**

```c
#include <stdio.h>

void test_locals(void) {
    int local_var = 1;
    const int const_local_var = 2;
    static int static_local_var = 0;

    local_var++;
    // const_local_var++; // compilation error if uncommented
    static_local_var++;

    printf("local_var: %d\n", local_var);
    printf("const_local_var: %d\n", const_local_var);
    printf("static_local_var: %d\n", static_local_var);
}

int main(void) {
    test_locals();
    test_locals();
    return 0;
}
```

**Expected output:**

```text
local_var: 2
const_local_var: 2
static_local_var: 1
local_var: 2
const_local_var: 2
static_local_var: 2
```

**Step-by-step:**

- أول ⁦call⁩: `local_var` يبدأ بـ1 ويبقى2؛ ⁦static⁩ تبدأ0 وتبقى1.
- تاني ⁦call⁩: `local_var` **تتخلق/تتهيأ مرة جديدة** بـ1، فتبقى2؛ `static_local_var` ما بتتصفّرش، فتبقى2.
- `const_local_var++` لو شلت `//` يبقى ⁦attempt to modify a const object⁩؛ ⁦compiler⁩ يرفض.

‏**⁦Exam trap⁩:** `static` ⁦local variable⁩ تحتفظ بالقيمة بين ⁦calls⁩، مش معناها إنها ⁦global visible⁩ لكل ⁦functions.⁩

---

## Part 6 — Lab 1

### Exercises from the Slide

السلايد فيها **7 ⁦problems⁩** لازم تتمرن عليهم:

1. **Rectangle**: Compute perimeter and area for height `7 inches` and width `5 inches`.
2. **Days conversion**: Convert a specified number of days into years, weeks and days.
3. **Distance**: Calculate distance between points `(x1, y1)` and `(x2, y2)`.
4. **Seconds conversion**: Convert an integer number of seconds to hours, minutes and seconds.
5. ‏**⁦Two integers⁩**: ⁦Read two integers and check⁩ “⁦if they are multiplied or not⁩” (ده نص السؤال في السلايد، لكنه يحتمل إن المقصود **⁦one is multiple of the other⁩**؛ لازم تتأكد من المقصود من المدرس).
6. **Month name**: Read integer `1..12`, print English month name.
7. **Divisibility**: Print numbers between `1..100` divisible by user-specified number.

**الفكرة من الـ ⁦Lab⁩:** تتدرب على ⁦arithmetic operators⁩, `%`, ⁦conditions⁩, `switch`, ⁦loops⁩, ⁦input/output.⁩

### Lab 1 — Suggested Practice Solutions (Extra explanation, not printed on slide)

**1. Rectangle — expected area `35`, perimeter `24`:**

```c
#include <stdio.h>
int main(void) {
    int height = 7, width = 5;
    int area = height * width;
    int perimeter = 2 * (height + width);
    printf("Area = %d, Perimeter = %d\n", area, perimeter);
    return 0;
}
```

**2. Days → years, weeks, days** (assuming one year = 365 days):

```c
int total_days = 400;
int years = total_days / 365;          // 1
int remainder = total_days % 365;     // 35
int weeks = remainder / 7;            // 5
int days = remainder % 7;             // 0
```

**3. Distance — Euclidean formula:**

$$
d = \sqrt{(x_2-x_1)^2 + (y_2-y_1)^2}
$$

```c
#include <math.h>
#include <stdio.h>
int main(void) {
    double x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    double dx = x2 - x1, dy = y2 - y1;
    double distance = sqrt(dx * dx + dy * dy); // 5.0
    printf("Distance = %.2f\n", distance);
    return 0;
}
```

> On some GCC-based systems you may need linking with `-lm` for math functions.

**4. Seconds → hours, minutes, seconds:**

```c
int total = 3671;
int hours = total / 3600;       // 1
int minutes = (total % 3600) / 60; // 1
int seconds = total % 60;       // 11
```

**5. If the intended question is “Is A a multiple of B?”:**

```c
int a = 20, b = 5;
if (b != 0 && a % b == 0) {
    printf("A is a multiple of B\n");
} else {
    printf("Not a multiple (or invalid B)\n");
}
```

ده حل لتفسير محتمل للسؤال، **مش حل مؤكد** لعبارة “⁦multiplied or not⁩” المكتوبة في المصدر.

**6. Month names (`switch`):**

```c
int month = 3;
switch (month) {
    case 1:  puts("January");   break;
    case 2:  puts("February");  break;
    case 3:  puts("March");     break;
    case 4:  puts("April");     break;
    case 5:  puts("May");       break;
    case 6:  puts("June");      break;
    case 7:  puts("July");      break;
    case 8:  puts("August");    break;
    case 9:  puts("September"); break;
    case 10: puts("October");   break;
    case 11: puts("November");  break;
    case 12: puts("December");  break;
    default: puts("Invalid month");
}
```

**7. Divisible numbers between 1 and 100:**

```c
int divisor = 7;
if (divisor != 0) {
    for (int i = 1; i <= 100; ++i) {
        if (i % divisor == 0) printf("%d ", i);
    }
}
```

‏**⁦Why⁩ `%`?** لأن ⁦remainder⁩ = `0` معناها القسمة على العدد صحيحة بدون باقي.

---

## Part 7 — Operators in C 

### What Is an Operator? / Arithmetic Operators

‏**⁦Operator⁩** = ⁦symbol⁩ بيقول للـ ⁦compiler⁩ يعمل ⁦operation⁩ معينة على **⁦operands⁩**.

```c
int result = 7 + 3;
// 7 and 3 = operands
// +       = operator
```

**Arithmetic operators in slide:**

| Operator | Name | Meaning | Example / Result |
|---|---|---|---|
| `+` | Addition | جمع | `8 + 2` ⇒ `10` |
| `-` | Subtraction | طرح | `8 - 2` ⇒ `6` |
| `*` | Multiplication | ضرب | `8 * 2` ⇒ `16` |
| `/` | Division | قسمة | `8 / 2` ⇒ `4` |
| `%` | Modulus / Remainder | باقي قسمة integer | `8 % 3` ⇒ `2` |
| `++` | Increment | +1 | `x++` |
| `--` | Decrement | −1 | `x--` |

**Integer division vs floating-point division:**

```c
int a = 10;
int b = 4;

int q = a / b;       // 2
int r = a % b;       // 2
float f = (float)a / b; // 2.5
```

- لو الاتنين ⁦integer types⁩، القسمة ⁦truncates fractional part toward zero.⁩
- باقي القسمة `%` بيشتغل مع ⁦integer operands⁩ مش ⁦float.⁩
- ‏⁦Division by zero⁩ / ⁦remainder by zero⁩ **⁦invalid⁩ / ⁦undefined behavior⁩** في ⁦C.⁩

**Pre-increment vs Post-increment:**

```c
int x = 5;
int a = ++x; // x becomes 6, a = 6

int y = 5;
int b = y++; // b = 5, then y becomes 6
```

لو الـ ⁦increment statement⁩ لوحدها `x++;` أو `++x;`، النتيجة النهائية للـ ⁦variable⁩ واحدة. الفرق بيظهر لما تستخدم قيمة ⁦expression⁩ نفسها.

### Arithmetic Examples from the Slide

السلايد فيها أمثلة تستخدم `printf` مع أنواع زي `int`, `float`، وبمثال آخر ⁦character⁩ مثل `'F'` مع ⁦number.⁩

**الفكرة المقصودة:** نوع ⁦operands⁩ يفرق في **⁦result type⁩** و**⁦format specifier⁩**.

```c
#include <stdio.h>

int main(void) {
    int op1 = 10;
    float op2 = 2.5f;

    printf("Add: %.2f\n", op1 + op2);     // 12.50
    printf("Subtract: %.2f\n", op1 - op2); // 7.50
    printf("Multiply: %.2f\n", op1 * op2); // 25.00
    printf("Divide: %.2f\n", op1 / op2);   // 4.00
    return 0;
}
```

‏**⁦Why⁩ `%.2f`?** يطبع ⁦floating result⁩ بـ ⁦two digits after decimal⁩؛ و`printf` ⁦arguments⁩ من `float` بتتحول تلقائيًا لـ `double` في ⁦variadic calls.⁩

**Character arithmetic:**

```c
char ch = 'F';
int n = 3;
int value = ch + n; // normally 70 + 3 = 73 on ASCII-based system
```

الـ `char` في ⁦arithmetic⁩ بيتعملها ⁦integer promotion⁩؛ فهي مش مجرد حرف ⁦visually.⁩ الرقم المرتبط بالحرف بيعتمد على ⁦execution character set⁩ (غالبًا ⁦ASCII-compatible⁩ على الأجهزة المعاصرة).

> [!warning] Format specifiers
> `%d` لـ `int`، `%u` لـ `unsigned int`، `%f` لطباعة ⁦floating values⁩ مع `printf`، و`%c` لطباعة ⁦character.⁩ غلط ⁦format⁩ مع ⁦argument type⁩ ممكن يعطي ناتج غلط أو ⁦undefined behavior⁩؛ مش مجرد مشكلة شكل.

###  Relational Operators

‏**⁦Relational⁩ / ⁦equality operators⁩** بتقارن ⁦values⁩ وبتطلع `1` لو ⁦condition true⁩ أو `0` لو ⁦false⁩ في ⁦C.⁩

| Operator | Meaning | Example |
|---|---|---|
| `==` | Equal to | `a == b` |
| `!=` | Not equal to | `a != b` |
| `>` | Greater than | `a > b` |
| `<` | Less than | `a < b` |
| `>=` | Greater than or equal | `a >= b` |
| `<=` | Less than or equal | `a <= b` |

```c
int a = 8, b = 5;
printf("%d\n", a > b);  // 1
printf("%d\n", a == b); // 0
printf("%d\n", a != b); // 1
```

**Very common mistake:**

```c
if (x == 5) { /* compare */ }
if (x = 5)  { /* assignment; value 5 => condition true */ }
```

- `==` = comparison.
- `=` = assignment.
- كتير من الـ ⁦compilers⁩ يطلعوا ⁦warning⁩ لو كتبت ⁦assignment⁩ بالخطأ جوه `if`.

**Embedded scenario:**

```c
if (temperature >= 70) {
    // Turn on fan
}
```

### Logical Operators: `&&`, `||`, `!`

| Operator | Meaning | True when... |
|---|---|---|
| `&&` | Logical AND | الشرطين true |
| `\|\|` | Logical OR | أي شرط true |
| `!` | Logical NOT | تقلب truth value |

**Truth table:**

| A | B | `A && B` | `A \|\| B` |
|---:|---:|---:|---:|
| 0 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 |
| 1 | 0 | 0 | 1 |
| 1 | 1 | 1 | 1 |

```c
int battery_ok = 1;
int button_pressed = 0;

if (battery_ok && button_pressed) {
    // Only if both are true
}

if (battery_ok || button_pressed) {
    // At least one is true
}

if (!button_pressed) {
    // Button is NOT pressed
}
```

‏**⁦Truth in C⁩:** `0 = false`، وأي `non-zero = true` (⁦including negative values⁩). نتائج ⁦logical operators⁩ نفسها بتكون `0` أو `1`.

**Short-circuit evaluation:**

```c
if (ptr != NULL && *ptr == 10) {
    // Safe: *ptr evaluated only if ptr is not NULL
}
```

- في `A && B`: لو `A` ⁦false⁩، `B` مش بتتقيّم.
- في `A || B`: لو `A` ⁦true⁩، `B` مش بتتقيّم.

> [!tip] Compare with bitwise
> `&&` و`||` بيشتغلوا على **⁦truth values⁩**؛ `&` و`|` بيشتغلوا على **⁦individual bits⁩**. الاتنين مختلفين تمامًا.

### Introduction to Bitwise Operators

الـ **⁦Bitwise operators⁩** بتخليك تتعامل مع الـ **⁦bits⁩** في ⁦memory⁩، وده من أهم أجزاء ⁦Embedded C⁩ عشان الـ ⁦registers⁩ و⁦bit flags.⁩

**Example of logical AND vs bitwise AND:**

```c
int a = 6; // 0110
int b = 3; // 0011

int logical = a && b; // 1: both are non-zero
int bitwise = a & b;  // 2: 0110 & 0011 = 0010
```

**ليه ⁦important⁩ في ⁦MCU⁩؟** كتير من ⁦hardware registers⁩ فيها ⁦bits⁩ كل واحدة مسؤولة عن ⁦feature⁩: ⁦enable⁩, ⁦status flag⁩, ⁦interrupt mask⁩, ⁦pin output⁩ ... إلخ.

### Bitwise Operators Table

| Operator | Name | Description |
|---|---|---|
| `&` | Bitwise AND | bit = 1 لو موجودة في **الاتنين** |
| `\|` | Bitwise OR | bit = 1 لو موجودة في **أي واحد** |
| `^` | Bitwise XOR | bit = 1 لو مختلفة بين الرقمين |
| `~` | Bitwise NOT / Complement | تقلب bits |
| `<<` | Left shift | shift bits ناحية الشمال |
| `>>` | Right shift | shift bits ناحية اليمين |

**Bit truth tables:**

| A | B | `A & B` | `A \| B` | `A ^ B` |
|---:|---:|---:|---:|---:|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 |

**Binary demonstration:**

```text
A = 12 = 00001100
B = 10 = 00001010
-----------------
A & B  = 00001000 = 8
A | B  = 00001110 = 14
A ^ B  = 00000110 = 6
```

‏**⁦Left shift⁩:** `5 << 1` على ⁦unsigned suitable type⁩ يساوي `10`:

```text
00000101 (5)  << 1  → 00001010 (10)
```

‏**⁦Right shift⁩:** `20 >> 2` على ⁦non-negative integers⁩ يساوي `5`:

```text
00010100 (20) >> 2  → 00000101 (5)
```

> [!warning] Shifts are NOT always simply ×2 or ÷2
> الـ ⁦rule⁩ ده مفيد للأرقام **⁦unsigned/⁩غير سالبة** لما النتيجة في المدى ومع ⁦shift count valid. Left shift⁩ على ⁦signed negative⁩ أو ⁦overflowing signed value⁩ فيه ⁦rules⁩ خطيرة، و⁦right shift⁩ على ⁦negative values⁩ يعتمد على ⁦standard/version/implementation.⁩ الأفضل للتعامل مع ⁦register masks⁩ استخدام ⁦unsigned types.⁩

### Bitwise Worked Example: `a = 60`, `b = 13`

السلايد بتستخدم:

```c
unsigned int a = 60; // low 8 bits: 00111100
unsigned int b = 13; // low 8 bits: 00001101
int c = 0;
```

**Results from the slide:**

| Expression | Binary (low 8 bits) | Decimal |
|---|---|---:|
| `a & b` | `00001100` | `12` |
| `a \| b` | `00111101` | `61` |
| `a ^ b` | `00110001` | `49` |
| `~a` | complement shown conceptually | source shows `-61` when assigned to `int` |
| `a << 2` | `11110000` | `240` |
| `a >> 2` | `00001111` | `15` |

**Walkthrough — AND:**

```text
   00111100  (60)
&  00001101  (13)
=  00001100  (12)
```

**OR:**

```text
   00111100  (60)
|  00001101  (13)
=  00111101  (61)
```

**XOR:**

```text
   00111100  (60)
^  00001101  (13)
=  00110001  (49)
```

‏**⁦Why is⁩ `~60 = -61` ⁦in the common signed view⁩?** في ⁦two⁩'⁦s complement⁩، `~x == -x - 1` عند تمثيل ⁦signed⁩ مناسب، وبالتالي `~60 = -61`.

> [!warning] Important clarification on slide 33
> لما المتغير `a` نوعه **`unsigned int`**، ⁦expression⁩ `~a` بتكون ⁦unsigned⁩، وقيمتها قبل التحويل لـ`int` تعتمد على ⁦width⁩ (`UINT_MAX - 60`). المثال في السلايد بيعرض `-61` بعد تخزين الناتج في ⁦signed⁩ `int` على بيئة معتادة. ما تعتبرش `~60` دائمًا `-61` من غير ما تراعي **⁦type/width/conversion⁩**.

‏**⁦Embedded bit masks⁩ — تقدر تعمل 4 ⁦operations⁩ مهمة جدًا:**

```c
#include <stdint.h>
uint8_t reg = 0b00000000;     // binary literal needs C23 or compiler extension
reg |=  (1u << 3);            // SET bit 3
reg &= (uint8_t)~(1u << 3);   // CLEAR bit 3
reg ^=  (1u << 3);            // TOGGLE bit 3
if (reg & (1u << 3)) {        // TEST bit 3
    // bit is set
}
```

‏**⁦Portable version note⁩:** لو ⁦compiler⁩ قديم ومش بيدعم `0b`, استخدم `0x00u` أو `0u`.

‏**⁦What is a mask⁩?** رقم فيه ⁦bits⁩ مختارة بتكون `1` عشان نحدد ⁦bits⁩ معينة داخل ⁦register.⁩

### Assignment Operator: `=`

‏**⁦Assignment⁩** = تخزين ⁦value⁩ في ⁦variable⁩ بعد حساب ⁦RHS expression.⁩

```c
int a;
a = 5;           // literal
int b = a;       // another variable
int c = a + 10;  // expression
```

- ‏**⁦Left-hand side⁩:** ⁦object⁩ قابل للتعديل (⁦modifiable lvalue⁩).
- ‏**⁦Right-hand side⁩:** ⁦expression⁩ بتحسب قيمتها الأول (من ناحية ⁦conceptual semantics⁩) وتتحول للنوع المناسب قبل التخزين.
- لا تخلط بين ⁦assignment⁩ `=` و⁦equality⁩ `==`.

**Assignment returns a value in expressions:**

```c
int x, y;
x = y = 10;  // both become 10 (assignment groups right-to-left)
```

### Compound Assignment Operators

بدل تكتب `x = x + n` ممكن تختصرها `x += n`، ونفس الفكرة مع باقي ⁦operators.⁩

| Operator | Equivalent idea | Example |
|---|---|---|
| `=` | assign | `x = 10` |
| `+=` | add and assign | `x += 2` |
| `-=` | subtract and assign | `x -= 2` |
| `*=` | multiply and assign | `x *= 2` |
| `/=` | divide and assign | `x /= 2` |
| `%=` | remainder and assign | `x %= 2` |
| `<<=` | left-shift and assign | `x <<= 2` |
| `>>=` | right-shift and assign | `x >>= 2` |
| `&=` | bitwise AND and assign | `x &= mask` |
| `^=` | bitwise XOR and assign | `x ^= mask` |
| `\|=` | bitwise OR and assign | `x \|= mask` |

**Example:**

```c
int x = 10;
x += 5;    // 15
x *= 2;    // 30
x /= 3;    // 10
x %= 4;    // 2
```

**Embedded examples:**

```c
GPIO_STATUS |=  (1u << 2); // set bit 2 (illustrative symbol)
GPIO_STATUS &= ~(1u << 2); // clear bit 2
```

> [!warning] Hardware register detail
> دي طريقة عامة للتعامل مع ⁦bits⁩، لكنها **مش آمنة مع كل ⁦peripheral register⁩** (مثلاً ⁦write-one-to-clear registers⁩ أو ⁦registers⁩ لها ⁦side effects⁩). ارجع دايمًا للـ ⁦datasheet⁩ و⁦vendor HAL.⁩ `GPIO_STATUS` هنا اسم توضيحي مش ⁦register⁩ قياسي.

### Ternary / Conditional Operator `?:`

**Syntax:**

```c
condition ? expression_if_true : expression_if_false
```

‏**⁦Why ternary⁩?** تختصر ⁦simple⁩ `if / else` إلى ⁦expression⁩ واحدة.

**The slide uses even/odd example:**

```c
int a = 10;
(a % 2 == 0) ? printf("%d is Even\n", a)
             : printf("%d is Odd\n", a);
```

**Equivalent if / else:**

```c
if (a % 2 == 0) {
    printf("Even\n");
} else {
    printf("Odd\n");
}
```

‏**⁦Important⁩:** `?:` بيرجع ⁦result expression⁩ من الفرع المختار، وبيعمل ⁦evaluate⁩ لفرع واحد فقط من الاتنين.

### More Ternary Examples / Largest Number

السلايد فيها مثالين لاختيار الأكبر بين `a=100` و`b=20`.

```c
int a = 100, b = 20;
int c = (a >= b) ? a : b;
printf("c = %d\n", c); // 100
```

**Flow:**

1. `a >= b` = `100 >= 20` = true.
2. اختار ⁦expression⁩ بعد `?` اللي هي `a`.
3. `c = 100`.

‏**⁦Nested⁩ / ⁦combined ternary example⁩** الموجود في الصورة بيجمع `printf` مع ⁦assignment⁩ في ⁦branch⁩؛ دي طريقة صعبة القراءة نسبيًا. الأفضل فصل الطباعة عن حساب `c` زي المثال اللي فوق.

> [!tip] Best practice
> استخدم ⁦ternary⁩ للـ ⁦simple value selection⁩، ولما ⁦logic⁩ تعقد استخدم `if / else` عشان ⁦readability.⁩

### Operator Precedence & Associativity

‏**⁦Precedence⁩** = أي ⁦operator⁩ بيرتبط بالـ ⁦operands⁩ أولًا في ⁦expression.⁩

‏**⁦Associativity⁩** = لو ⁦operators⁩ لهم نفس ⁦precedence⁩، بتتجمع ⁦expressions⁩ بأي اتجاه؟

**Order shown in the slide (highest → lowest):**

| Priority | Category | Operators | Associativity |
|---:|---|---|---|
| 1 | Postfix | `()`, `[]`, `.`, `->`, postfix `++`, postfix `--` | Left → Right |
| 2 | Unary | unary `+`, unary `-`, `!`, `~`, prefix `++`, prefix `--`, `(type)`, `*`, `&`, `sizeof` | Right → Left |
| 3 | Multiplicative | `*`, `/`, `%` | Left → Right |
| 4 | Additive | `+`, `-` | Left → Right |
| 5 | Shift | `<<`, `>>` | Left → Right |
| 6 | Relational | `<`, `<=`, `>`, `>=` | Left → Right |
| 7 | Equality | `==`, `!=` | Left → Right |
| 8 | Bitwise AND | `&` | Left → Right |
| 9 | Bitwise XOR | `^` | Left → Right |
| 10 | Bitwise OR | `\|` | Left → Right |
| 11 | Logical AND | `&&` | Left → Right |
| 12 | Logical OR | `\|\|` | Left → Right |
| 13 | Conditional | `?:` | Right → Left |
| 14 | Assignment | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=`, `&=`, `^=`, `\|=` | Right → Left |
| 15 | Comma | `,` | Left → Right |

**Examples:**

```c
int x = 2 + 3 * 4;    // 14, multiplication before addition
int y = (2 + 3) * 4;  // 20, parentheses override

int z = 1 + 2 << 2;   // (1+2)<<2 = 12
```

**Bitwise/relational tricky case:**

```c
int a = 6, b = 3;
int result1 = a & b == 3;      // a & (b == 3) = 6 & 1 = 0
int result2 = (a & b) == 3;    // (6 & 3) == 3 = (2 == 3) = 0
```

لأن المثالين فوق طلعوا نفس الرقم رغم الـ ⁦grouping⁩ المختلف، نخلي مثال أوضح:

```c
int a = 6, b = 2;
int p = a & b == 2;       // a & (b == 2) = 6 & 1 = 0
int q = (a & b) == 2;     // (6 & 2) == 2 = 1
```

**Important distinction:**

- ‏**⁦Precedence is NOT the same as evaluation order.⁩** الـ ⁦table⁩ بتحدد ⁦grouping⁩، مش ترتيب حدوث كل ⁦side effects.⁩
- بلاش ⁦expressions⁩ فيها ⁦multiple unsequenced modifications⁩ لنفس ⁦variable⁩، زي `i++ + ++i`؛ قد تكون ⁦undefined behavior.⁩
- أحسن ⁦practice⁩ في ⁦embedded code⁩ الحسّاس: **⁦parentheses⁩** حتى لو حافظ ⁦precedence⁩، عشان ⁦clarity.⁩

---

## Part 8 — Decision Making & Switch

### Decision Making / Control Flow

‏**⁦By default⁩:** البرنامج بينفذ ⁦statements sequentially⁩ من فوق لتحت.

‏**⁦Decision-making⁩** بتسمح للكود يختار ⁦branch⁩ مختلف حسب ⁦condition.⁩

```text
        [ Check condition ]
         /            \
      True            False
       |                |
 [then code]       [skip/else]
       \                /
        [ Continue program ]
```

**Conceptual C example:**

```c
int temperature = 35;
if (temperature > 30) {
    printf("Fan ON\n");
} else {
    printf("Fan OFF\n");
}
```

‏**⁦Difference to remember⁩:** ⁦decision branches choose⁩ *⁦what executes⁩*؛ ⁦loops⁩ (الجزء اللي بعده) بتحدد *⁦how many times code repeats⁩*.

### `switch` Case: Multi-way Branching

**`switch`** بتقارن **⁦one integral expression⁩** بمجموعة **⁦constant case labels⁩**.

‏**⁦When useful⁩?** لما عندك ⁦mode⁩ أو ⁦menu⁩ أو ⁦status code⁩ وقيم محددة كتير:

```c
int mode = 2;
switch (mode) {
    case 0:
        puts("OFF");
        break;
    case 1:
        puts("IDLE");
        break;
    case 2:
        puts("RUNNING");
        break;
    default:
        puts("UNKNOWN");
        break;
}
```

**Output:** `RUNNING`.

**`switch` vs `if / else`:**

- `switch`: مناسب لما تختبر ⁦equality⁩ مع ⁦discrete constant values.⁩
- `if / else`: مناسب للـ ⁦ranges⁩ والـ ⁦compound conditions⁩ مثل `temperature > 30 && humidity < 50`.

### Switch Statement Rules (Part 1)

**Rules from slide:**

1. ‏**⁦Expression type⁩:** `switch` ⁦expression⁩ نوعها ⁦integral type⁩ (`int`, `char`, إلخ) أو ⁦enum.⁩ **⁦C++⁩** تسمح بحالات ⁦class conversion⁩ معينة؛ ده اختلاف بين ⁦C⁩ و⁦C++⁩ مذكور في السلايد.
2. ‏**⁦Cases⁩:** ينفع يكون في أي عدد من `case` ⁦labels⁩ (طبعًا ضمن حدود ⁦compiler/resources⁩)، وكل واحدة بعدها `:`.
3. ‏**⁦Case values⁩:** لازم **⁦integer constant expressions⁩** قابلة للمقارنة مع النوع بعد ⁦integer promotions⁩؛ مش ⁦runtime variables.⁩

```c
int value = 2;
int other = 3;

switch (value) {
    case 1: puts("one"); break;
    case 2: puts("two"); break;
    // case other: ...  // invalid: other is not an integer constant expression
}
```

**Extra clarity:**

- ‏⁦case values⁩ لازم تبقى **⁦unique⁩** بعد ⁦conversion⁩؛ مينفعش ⁦duplicate case labels.⁩
- `switch` على `float` أو ⁦string⁩ مباشرة مش متاح في ⁦standard C.⁩
- ‏⁦Variables⁩ من ⁦type⁩ `enum` مناسبة جدًا لـ ⁦state machines.⁩

### Switch Rules (Part 2): `break`, Fall-through & `default`

**4. `break`** → يخرج فورًا من أقرب `switch` أو ⁦loop⁩ ويمشي للسطر اللي بعده.

**5. ⁦Fall-through⁩** → لو ⁦case⁩ من غير `break`، التنفيذ يكمل في الـ ⁦case⁩ اللي بعدها، حتى لو الـ ⁦labels⁩ مش ⁦matching.⁩

**6. `default`** → ⁦optional⁩، بتشتغل لو مفيش ⁦case matches.⁩ لو هي آخر واحدة مش لازم `break` لسبب الخروج، لكن ممكن تضيفها للـ ⁦consistency.⁩

**Fall-through demonstration:**

```c
int x = 1;
switch (x) {
    case 1:
        puts("ONE");
        // no break!
    case 2:
        puts("TWO");
        break;
    default:
        puts("OTHER");
}
```

**Output:**

```text
ONE
TWO
```

**ليش؟** بدأ ينفذ عند `case 1` وبعدها كمل لـ `case 2` لحد ما شاف `break`.

> [!warning] Important
> بعض ⁦bugs⁩ في الـ ⁦switch⁩ سببها نسيان `break`. أحيانًا ⁦fall-through⁩ يكون ⁦intentional⁩؛ في الحالة دي حط ⁦comment⁩ واضح عشان اللي يقرأ الكود يعرف.

### Switch Examples with Characters

الصورة فيها أمثلة بـ ⁦characters⁩ (زي `'a'` و`'g'`) وتصنيف **⁦lowercase⁩ / ⁦uppercase⁩ / ⁦digit⁩ / ⁦other⁩** و⁦cases⁩ مجمعة.

**Example 1 — grouped labels:**

```c
char c = 'a';
switch (c) {
    case 'a':
    case 'b':
    case 'c':
        puts("one of a, b, c");
        break;
    case 'x':
        puts("letter x");
        break;
    default:
        puts("another character");
}
```

**الفكرة:** مجموعة ⁦case labels⁩ ممكن تشترك في نفس الكود؛ مفيش ⁦statements⁩ بينها، وبالتالي ⁦intentional fall-through.⁩

**Example 2 — character categories (representative of the slide):**

```c
char ch = 'g';

switch (ch) {
    case 'g':
    case 'z':
        puts("Recognized lowercase letter");
        break;
    case 'A':
    case 'Z':
        puts("Recognized uppercase letter");
        break;
    case '0':
    case '5':
        puts("Recognized digit");
        break;
    default:
        puts("Other character");
}
```

‏**⁦Note⁩:** ده ⁦matching⁩ لقيم مختارة، **مش** تصنيف لكل حروف ⁦alphabet.⁩ لو عايز كل ⁦lowercase/uppercase/digits⁩، استخدم `ctype.h` ⁦functions⁩ (مع مراعاة ⁦casts⁩ المطلوبة) أو `if` ⁦ranges⁩ لو ⁦encoding⁩ مناسب.

---

## Part 9 — Loops & Flow Control

### What Is a Loop? / Loop Classification

‏**⁦Loop⁩** = ⁦block of statements⁩ بيتنفذ بشكل متكرر لحد ما ⁦condition⁩ توصل لقيمة معينة أو عدد ⁦iterations⁩ يخلص.

**Classification in slide:**

```text
Loops
├── Entry-controlled (condition checked BEFORE body)
│   ├── for
│   └── while
└── Exit-controlled (condition checked AFTER body)
    └── do-while
```

‏**⁦Entry-controlled⁩:** ممكن ⁦body⁩ ما تتنفذش ولا مرة لو ⁦condition false⁩ من البداية.

‏**⁦Exit-controlled⁩:** ⁦body⁩ بتتنفذ **مرة واحدة على الأقل**؛ لأن ⁦condition⁩ بعدها.

**Keywords:**

- ‏**⁦Iteration⁩:** دورة واحدة من تنفيذ ⁦loop.⁩
- ‏**⁦Condition⁩:** ⁦expression⁩ بتحدد نكمل ولا نوقف.
- ‏**⁦Loop body⁩:** الكود اللي بيتكرر.
- ‏**⁦Initialization⁩:** إعداد ⁦counter⁩ قبل أو عند بداية ⁦loop.⁩
- ‏**⁦Update⁩:** تغيير ⁦counter⁩ أو ⁦state⁩ علشان نوصل لنقطة توقف.

**Why useful in Embedded?** Polling sensor, repeating output, processing buffers, checking flags, doing periodic software tasks.

###  `for` Loop Syntax & Examples

**Syntax in slide:**

```c
for (initialization; condition; increment_or_decrement) {
    // statements
}
```

**Execution order:**

```text
1. initialization  (once)
2. condition       (before each iteration)
3. body            (when condition true)
4. update          (after each iteration)
5. go back to condition
```

**Standard example:**

```c
for (int a = 1; a <= 5; a++) {
    printf("a: %d\n", a);
}
```

‏**⁦Output⁩:** `1`, `2`, `3`, `4`, `5` كل رقم في سطر.

**Slide example A — omitted initialization:**

```c
int a = 1;
for (; a <= 5; a++) {
    printf("a: %d\n", a);
}
```

`initialization` ممكن يبقى فاضي لأن `a` اتهيأت قبل الـ⁦loop⁩، لكن لازم تحافظ على الـ ⁦semicolons⁩ داخل `for( ; ; )`.

**Slide example B — omitted update:**

```c
int a;
for (a = 1; a <= 5; ) {
    printf("a: %d\n", a);
    a++; // update inside the loop body instead
}
```

**Slide example C — omitted condition and `break`:**

```c
int a;
for (a = 1; ; a++) {
    printf("a: %d\n", a);
    if (a == 5) break;
}
```

غياب الـ⁦condition⁩ من `for` يجعلها ⁦conceptually true⁩ دائمًا، لكن `break` ممكن يوقفها.

**Slide example D — multiple expressions:**

```c
int a, b;
for (a = 1, b = 1; a <= 5; a++, b++) {
    printf("a:%d b:%d a*b:%d\n", a, b, a * b);
}
```

- فيه `comma operator` بيخلّيك تستخدم أكثر من ⁦initialization⁩ / ⁦update expression.⁩
- هنا الاتنين ⁦counters⁩ بيتحركوا مع بعض.

**Watch out — Off-by-one:**

```c
for (int i = 0; i < 5; i++)  // 5 iterations: 0..4
for (int i = 0; i <= 5; i++) // 6 iterations: 0..5
```

‏**⁦When should you use⁩ `for`?** غالبًا لما عدد ⁦iterations⁩ واضح، زي ⁦loop⁩ على ⁦array⁩ أو عدد ⁦readings⁩ معين.

### `while` Loop: What Is an Expression?

السلايد بتشرح الأول معنى **⁦Expression⁩**:

- حاجة يمكن ⁦evaluation⁩ ليها فتنتج **⁦value⁩**.
- ‏⁦Examples⁩: `5 + 3` ⇒ `8`، `x > 0` ⇒ `1 or 0`، `a = b + 2` ⇒ ⁦assigned value.⁩
- في `while(expression)`، أي ⁦result⁩ **⁦non-zero⁩** بيتفسّر ⁦true⁩؛ `0` ⁦false.⁩

**Syntax:**

```c
while (condition) {
    // repeatedly executed statements
}
```

**Example:**

```c
int i = 1;
while (i <= 5) {
    printf("%d\n", i);
    i++;
}
```

**Execution trace:**

| Before check `i` | `i <= 5` | What happens |
|---:|---|---|
| 1 | true | print 1, increment to 2 |
| 2 | true | print 2, increment to 3 |
| 3 | true | print 3, increment to 4 |
| 4 | true | print 4, increment to 5 |
| 5 | true | print 5, increment to 6 |
| 6 | false | exit loop |

‏**⁦Common bug⁩:** لو نسيت `i++`، ⁦condition⁩ هتفضل ⁦true⁩ وقد تحصل ⁦Infinite Loop.⁩

### What Is a Statement? / `break` & `continue` in `while`

‏**⁦Statement⁩** = ⁦instruction⁩ أو ⁦construct⁩ بيعمل ⁦action⁩ في البرنامج، مثل:

```c
x = x + 1;       // expression statement
printf("Hello"); // function-call expression statement
break;           // jump statement
```

**Important concept:**

- ‏**⁦Expression⁩** بتنتج ⁦value.⁩
- ‏**⁦Statement⁩** بتنظم تنفيذ ⁦code⁩ أو بتنفّذ ⁦expression⁩ كتعليمة.

**While structure in slide:**

```c
while (expression) {
    // statements
    if (condition1) {
        break;
    }
    if (condition2) {
        continue;
    }
}
```

**Meaning:**

- `break` يخرج من ⁦loop⁩ بالكامل.
- `continue` يتخطى بقية **⁦current iteration⁩** ويروح لفحص `while` ⁦condition⁩ تاني.

**Example:**

```c
int i = 0;
while (i < 6) {
    i++;
    if (i == 3) continue;
    if (i == 5) break;
    printf("%d ", i);
}
// prints: 1 2 4
```

**Walkthrough:**

- `i=3`: `continue` يتخطى `printf`.
- `i=5`: `break` يخرج من ⁦loop.⁩

> [!warning] Statement/expression nuance
> السلايد بتقول إن ⁦statements⁩ «⁦do not produce a value that can be used elsewhere⁩» كشرح تعليمي مبسط. في ⁦C⁩ مثلًا `x = x + 1` هي **⁦assignment expression⁩** داخل **⁦expression statement⁩**؛ التعبير نفسه ليه ⁦value⁩ لكن ⁦statement⁩ الكاملة مش ⁦operand⁩ في ⁦expression⁩ أكبر.

### `do-while` Loop

**Syntax in slide:**

```c
do {
    // statements
} while (condition);
```

‏**⁦Main difference⁩:** الشرط بيتفحص **بعد** ⁦body⁩؛ يعني ⁦loop body⁩ هتشتغل مرة واحدة على الأقل، حتى لو الشرط ⁦false⁩ من الأول.

**Slide example:**

```c
#include <stdio.h>

int main(void) {
    int a = 1;
    do {
        printf("Hello World\n");
        a++;
    } while (a <= 5);
    printf("End of Loop");
    return 0;
}
```

**What happens?**

- `a=1..5`: تطبع `Hello World` خمس مرات.
- بعد ⁦iteration⁩ الخامسة `a=6`، ⁦condition false⁩، فيخرج ويطبع `End of Loop`.

**Example highlighting difference:**

```c
int x = 10;
while (x < 5) {
    puts("while");  // not printed
}

do {
    puts("do-while"); // printed once
} while (x < 5);
```

‏**⁦Use case⁩:** ⁦menu⁩ لازم يتعرض للمستخدم مرة قبل ما يتأكد إذا كان عايز يكمل، أو عملية ⁦check⁩ لازم تتم أول مرة قبل ⁦condition⁩ بتاعت الإعادة.

### Nested Loops

‏**⁦Nested loop⁩** = ⁦loop⁩ جوه ⁦loop⁩ تانية.

```text
Outer iteration 1
    Inner iteration 1
    Inner iteration 2
    Inner iteration 3
Outer iteration 2
    Inner iteration 1
    Inner iteration 2
    Inner iteration 3
...
```

**Slide shows multiplication tables 1 to 10:**

```c
#include <stdio.h>

int main(void) {
    int i, j;
    printf("Tables from 1 to 10\n");

    for (i = 1; i <= 10; i++) {       // Outer loop: table number
        for (j = 1; j <= 10; j++) {   // Inner loop: multiplier
            printf("%4d", i * j);
        }
        printf("\n");  // new row after each outer iteration
    }
    return 0;
}
```

**Trace for the first two outer iterations:**

- `i=1` → `j=1..10` → print `1, 2, 3, ..., 10`.
- `i=2` → `j=1..10` → print `2, 4, 6, ..., 20`.

‏**⁦How many operations⁩?** `10 outer × 10 inner = 100` ⁦body executions⁩ في المثال ده.

‏**⁦What is⁩ `%4d`?** ⁦format specifier⁩ يحجز **⁦minimum width of⁩ 4 ⁦characters⁩** للعدد، فالأعمدة بتطلع ⁦aligned.⁩

‏**⁦Embedded relevance⁩:** ⁦loops nested⁩ شائعة في ⁦image buffers⁩ أو 2D ⁦matrices⁩، بس لازم تراقب ⁦execution time⁩؛ لو `outer=N`, `inner=M` فعدد ⁦iterations⁩ عادة `N×M`.

### Infinite Loops

‏**⁦Infinite loop⁩** = مفيش نهاية طبيعية طالما مفيش ⁦exit condition⁩ أو `break` / ⁦reset⁩ / ⁦external control.⁩

**Common forms in slide:**

```c
while (1) {
    printf("Hello World\n");
}
```

```c
for (;;) {
    // Forever
}
```

```c
do {
    // Forever
} while (1);
```

‏**⁦Slide also demonstrates a⁩ `while(i < 10)` ⁦case where⁩ `i` ⁦increments⁩:** دي **مش** ⁦infinite loop⁩؛ بتنتهي بمجرد `i` يوصل لـ10 (حتى لو ⁦heading⁩ عام بعنوان ⁦Infinite Loop⁩).

**What is the typical embedded pattern?**

```c
int main(void) {
    // setup_clocks();
    // init_gpio();
    // init_uart();

    while (1) {
        // read sensors
        // update control logic
        // handle application state
    }
}
```

ليه ⁦main loop⁩ دايمًا شغالة؟ لأن الجهاز لازم يفضل **⁦Monitoring⁩ / ⁦Controlling⁩** طول ما ⁦power⁩ موجودة، مش يخلص ويقفل زي برنامج ⁦desktop⁩ عادي.

**Danger:**

- ‏⁦Infinite loop⁩ فيها `printf` ⁦nonstop⁩ ممكن تستهلك ⁦CPU⁩ أو ⁦UART bandwidth.⁩
- الـ ⁦loops⁩ اللي بتعمل **⁦busy waiting⁩** بتستهلك ⁦power⁩؛ أحيانًا الأفضل ⁦interrupts⁩ أو ⁦sleep modes.⁩
- في الأنظمة اللي فيها **⁦watchdog⁩**، لازم ⁦firmware⁩ ينفذ ⁦service conditions⁩ المطلوبة عشان ما يحصلش ⁦unwanted reset.⁩

### `break` Statement vs `continue` Statement

**`break`:** Exit the nearest enclosing loop or `switch` immediately.

**`continue`:** Skip the rest of the current iteration and move to the next iteration of the loop.

**Compare:**

| Keyword | Meaning | Where control goes |
|---|---|---|
| `break` | Stop the loop/switch | After loop/switch |
| `continue` | Skip this iteration's remaining statements | Next condition/update cycle |

**Slide's `continue` example:**

```c
#include <stdio.h>

int main(void) {
    int i = 0;
    while (i < 10) {
        i++;
        if (i % 2 == 0) {
            continue;  // skip even numbers
        }
        printf("i: %d\n", i);
    }
    return 0;
}
```

**Printed:** `1, 3, 5, 7, 9`.

**Detailed flow:**

- Iteration with `i=1`: odd → don't continue → print.
- `i=2`: even → continue → skip print.
- Repeat up to `i=10`; then `while (i < 10)` becomes false.

**Different result with `break`:**

```c
for (int i = 1; i <= 10; i++) {
    if (i == 4) break;
    printf("%d ", i);
}
// 1 2 3
```

**`continue` in a `for` loop:** jump happens to the **update expression**, then condition. In a `while`, jump goes to **condition**. In a `do-while`, jump goes to the **condition at the bottom**.

> [!warning] Frequent pitfall
> لو عندك `while` وكتبت `continue` قبل `i++`، ممكن تعلق في ⁦infinite loop.⁩ خلي بالك إن ⁦counter⁩ يتحدّث قبل ما تتخطّى باقي الـ ⁦body.⁩

**Example of the pitfall:**

```c
// BAD example — do not run blindly:
int i = 0;
while (i < 5) {
    if (i == 2) continue; // no i++ when i==2 -> stuck forever
    i++;
}
```

---

## Part 10 — `goto` in C

### `goto` Statement: Purpose & Control Flow

**`goto`** = **⁦unconditional jump⁩** إلى **⁦label⁩** في **نفس ⁦function⁩**.

**Syntax:**

```c
goto LABEL;

LABEL:
    /* statements */
```

**Key points from slide:**

1. ينقل ⁦control⁩ لـ ⁦statement⁩ بعد ⁦label.⁩
2. الـ ⁦label⁩ لازم يكون جوه نفس ⁦function⁩، مينفعش تقفز لوظيفة تانية بـ `goto`.
3. ‏**⁦Forward jump⁩:** ⁦label⁩ تيجي بعد `goto` في الكود.
4. ‏**⁦Backward jump⁩:** ⁦label⁩ قبل `goto`، وممكن يعمل ⁦repeated behavior⁩ مشابه للـ ⁦loop.⁩
5. استخدامه كتير يضر ⁦readability⁩ و⁦maintainability⁩، فغالبًا استخدم `for` أو `while` بدلًا منه.

**Forward jump example:**

```c
#include <stdio.h>
int main(void) {
    puts("Before jump");
    goto SKIP;

    puts("This is skipped");
SKIP:
    puts("After jump");
    return 0;
}
```

**Output:**

```text
Before jump
After jump
```

**Backward jump — conceptual loop:**

```c
int i = 0;
AGAIN:
    printf("%d\n", i);
    i++;
    if (i < 3) goto AGAIN;
// Prints 0, 1, 2
```

**Structured alternative (better for this case):**

```c
for (int i = 0; i < 3; i++) {
    printf("%d\n", i);
}
```

### Why Avoid `goto`?

**السلايد بتذكر الأسباب الآتية:**

1. ممكن يعمل ⁦jump⁩ بعيد في نفس ⁦function⁩، فيصعب تتبّع ⁦program flow.⁩
2. الاستخدام المكثّف يؤدي إلى **⁦spaghetti code⁩** وتداخل ⁦entry/exit points.⁩
3. ‏**⁦Edsger Dijkstra⁩** كان من أبرز من انتقدوا الإفراط في `goto` ودعوا إلى ⁦structured programming.⁩
4. لغات حديثة كتير لا توفر `goto` أصلًا، لكنه موجود في ⁦C⁩ و⁦C++.⁩
5. بدائل أفضل: `if / else`, `for`, `while`, `break`, `continue`, ⁦functions.⁩ السلايد تذكر **⁦exception handling⁩** ضمن البدائل العامة؛ ده موجود في لغات/⁦C++⁩ لكنه **مش ⁦mechanism⁩ قياسي في ⁦C⁩**.
6. استخدم `goto` فقط لما يكون له مبرر واضح ومفيش ⁦structure⁩ أبسط.

**Bad readability scenario:**

```c
if (a) goto STEP3;
STEP1: /* ... */
if (b) goto END;
STEP3: /* ... */
if (c) goto STEP1;
END:   /* ... */
```

المثال ده توضيحي للـ ⁦spaghetti control flow⁩، مش ⁦logic⁩ مطلوب تتبعه.

**When is `goto` sometimes used legitimately in C?**

في ⁦error handling⁩ / ⁦cleanup⁩، خصوصًا لما ⁦resources⁩ تتفتح على مراحل ومحتاج تقفل اللي اتفتح قبل ⁦return.⁩ المثال التالي **توضيح إضافي** خارج السلايد:

```c
#include <stdio.h>

int process_file(void) {
    FILE *f = fopen("data.bin", "rb");
    if (f == NULL) return -1;

    // Imagine more operations here...
    if (ferror(f)) goto cleanup;

    fclose(f);
    return 0;

cleanup:
    fclose(f);
    return -1;
}
```

‏**⁦Why acceptable sometimes⁩?** لأنه ⁦jump⁩ واضح إلى `cleanup` واحد داخل ⁦function⁩، بدل ⁦duplicate resource-release code.⁩ لكن لو مفيش سبب قوي، ⁦structured flow⁩ أبسط وأحسن.

---

## Quick Revision — One-Page Cheat Sheet

### Core Embedded Concepts

| Concept | Remember |
|---|---|
| Embedded C | C + hardware access + resource constraints |
| Toolchain | Editor → Compiler/Assembler → Linker → ELF/HEX/BIN → Flasher |
| MCU memory | Flash للcode/initializers، RAM للwritable runtime data |
| `.text` | executable instructions |
| `.rodata` | read-only data / constants (usual) |
| `.data` | initialized writable globals/statics |
| `.bss` | zero-initialized globals/statics |
| Stack | function calls / automatic locals (typically) |
| Heap | dynamic allocations (if present) |
| `extern` | declaration of name/object elsewhere |
| `static` local | value survives between calls |
| `const` | can't modify through const-qualified lvalue |
| `volatile` | value can change outside ordinary code flow |
| `signed` | negative and non-negative values |
| `unsigned` | non-negative values; watch conversion/wrap |
| `uint8_t` | exactly 8-bit unsigned integer, if supported |

### Operators at a Glance

| Category | Operators |
|---|---|
| Arithmetic | `+ - * / % ++ --` |
| Comparison | `== != > < >= <=` |
| Logical | `&&`, `\|\|`, `!` |
| Bitwise | `&`, `\|`, `^`, `~`, `<<`, `>>` |
| Assignment | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, shifts/bitwise assignments |
| Conditional | `?:` |

### Bit Operations — The Four Classics

```c
// Bit index n (example: 3)
value |=  (1u << n);   // set bit n
value &= ~(1u << n);   // clear bit n
value ^=  (1u << n);   // toggle bit n
if (value & (1u << n)) // test bit n
```

> استخدم ⁦unsigned value⁩ مناسب وعرض ⁦bit index valid.⁩ لو ⁦hardware register⁩ له ⁦special semantics⁩، اقرأ ⁦datasheet⁩ قبل أي ⁦read-modify-write operation.⁩

### Loops in One Table

| Loop | Condition checked | Guaranteed minimum body executions | Best use |
|---|---|---:|---|
| `for` | Before | 0 | Known/structured counter |
| `while` | Before | 0 | Repeat while condition holds |
| `do-while` | After | 1 | First execution always needed |

### `break` / `continue` / `goto`

- **`break`** = خرج من أقرب ⁦loop⁩ أو ⁦switch.⁩
- **`continue`** = Skip remaining statements in current loop iteration.
- **`goto`** = ⁦Jump to label in same function⁩؛ تجنبه في ⁦flow⁩ العادي.

---

## Common Exam Traps & Important Clarifications

### Types & Casting

1. `int`/`long` ⁦size⁩ **مش ⁦constant⁩** بين ⁦MCUs⁩؛ ⁦always check target.⁩
2. `sizeof(type)` بيرجع ⁦size⁩ بـ ⁦C bytes⁩؛ ⁦byte width⁩ مش بالضرورة 8 ⁦bits⁩ على كل ⁦implementation.⁩
3. `float x = 5 / 2;` ⇒ `2.0` مش `2.5`، لأن ⁦integer division⁩ تمت أولًا.
4. `uint8_t` من `0..255`؛ `int8_t` من `−128..127`.
5. تحويل `300` إلى 8-⁦bit⁩ **⁦unsigned⁩** ⇒ `44`، لكن التحويل لنوع ⁦signed out-of-range⁩ يحتاج حذر.
6. `uint8_t a = 200, b = 100; uint8_t c = a + b;` ⇒ `44` في الحالة المعتادة؛ استخدم ⁦destination⁩ أوسع لو عايز `300`.
7. ‏**⁦Signed overflow⁩ = ⁦undefined behavior⁩**، ما تعمّمش ⁦unsigned wrap rule⁩ عليه.
8. `char` مش بالضرورة ⁦signed⁩ على كل ⁦targets.⁩

### Memory & Variables

1. ‏**⁦Declaration vs definition⁩**: `extern int x;` ⁦declaration⁩، أما `int x = 10;` ⁦definition.⁩
2. ‏**⁦Scope⁩ ≠ ⁦lifetime⁩**: ⁦local static⁩ متغير محلي في الرؤية لكنه طويل العمر.
3. `const` مش ⁦automatically⁩ «⁦stored in ROM⁩»؛ ⁦compiler/linker/platform⁩ يحددوا مكانها.
4. `volatile` مش ⁦atomic⁩ وما بيمنعش ⁦race conditions.⁩
5. `.data` بتحتاج ⁦initialized runtime data⁩ في ⁦RAM⁩، ⁦initial image⁩ ممكن تكون في ⁦Flash.⁩
6. `.bss` بتتصفر عند ⁦startup⁩ (في بيئات ⁦runtime⁩ التقليدية).
7. ‏⁦Heap⁩ اختيارية؛ ⁦stack capacity⁩ صغيرة ممكن تعمل ⁦stack overflow.⁩

### Operators & Control Flow

1. `=` assignment / `==` equality.
2. `&&` logical AND / `&` bitwise AND.
3. `||` logical OR / `|` bitwise OR.
4. ‏⁦Bitwise masks⁩ الأفضل يكون نوعها ⁦unsigned.⁩
5. `~` محتاجة فهم ⁦promoted type⁩ و⁦width⁩؛ مش مجرد ⁦flip⁩ لـ 8 ⁦bits⁩ تلقائيًا.
6. ‏⁦Always check precedence⁩؛ استخدم ⁦parentheses⁩ خاصة مع ⁦bitwise⁩ + ⁦comparison.⁩
7. `switch` لا يقبل `float` مباشرة ولا `case` ⁦runtime variable⁩ في ⁦standard C.⁩
8. نسيان `break` في `switch` يعمل ⁦fall-through.⁩
9. `for (i=0; i<5; i++)` خمس مرات، مش أربع ولا ست.
10. `do-while` ⁦body⁩ تتنفذ مرة على الأقل.
11. `continue` في `while` قبل ⁦counter update⁩ ممكن يعمل ⁦infinite loop.⁩
12. `goto` داخل نفس ⁦function⁩ فقط؛ ⁦exception handling⁩ مش ⁦feature⁩ قياسي في ⁦C.⁩

---

## Practice Questions — Self Check (Extra Revision)

> [!question] Q1
> On a given AVR target, `int` can be 16-bit. Why is it wrong to assume that `sizeof(int) == 4` on every microcontroller?

> [!question] Q2
> What is the difference between a declaration and a definition? Give an example with `extern`.

> [!question] Q3
> Why might a flag modified by an ISR need `volatile`? Does `volatile` guarantee atomic access?

> [!question] Q4
> Which segments usually hold initialized global variables, uninitialized globals, function code, and function-local automatic variables?

> [!question] Q5
> What happens to `uint8_t result = 200 + 100;` and why? (Assume `uint8_t` exists.)

> [!question] Q6
> Compute `60 & 13`, `60 | 13`, `60 ^ 13`, `60 << 2`, `60 >> 2`.

> [!question] Q7
> Explain the difference between `&&` and `&` with values `a=6`, `b=3`.

> [!question] Q8
> What is the output of:
>
> ```c
> int a = 1;
> switch (a) {
>     case 1: puts("A");
>     case 2: puts("B"); break;
>     default: puts("C");
> }
> ```

> [!question] Q9
> What is the difference between `while` and `do-while` when the initial condition is false?

> [!question] Q10
> When should you prefer a `for` loop? What's the difference between `break` and `continue`?

> [!question] Q11
> What is `goto` allowed to jump to? Why is it normally discouraged?

> [!question] Q12
> How would you use a bitmask to SET, CLEAR, TOGGLE and TEST bit 3 in a register?

### Self-Check Answers

1. Standard C defines minimum ranges and ordering rules, not an identical size for all implementations; target ABI/compiler matter.
2. Declaration announces name/type; definition provides object/function. `extern int speed;` declaration; `int speed = 5;` definition.
3. Hardware/ISR may change value unexpectedly; volatile preserves relevant accesses, but does **not** guarantee atomicity.
4. `.data`, `.bss`, `.text`, stack/registers respectively (typical layout).
5. `300` stored in unsigned 8-bit destination ⇒ `44` modulo 256.
6. `12`, `61`, `49`, `240`, `15` respectively.
7. `6 && 3` = `1`; `6 & 3` = `2`.
8. Prints `A`, then `B` because `case 1` lacks `break`.
9. `while` may execute zero times; `do-while` executes once at least.
10. `for` for clear counted iterations; `break` exits, `continue` skips current iteration's remaining body.
11. A label in the same function. Excessive jumps make control flow difficult to read/maintain.
12. `r |= (1u<<3);`, `r &= ~(1u<<3);`, `r ^= (1u<<3);`, `if (r & (1u<<3)) ...`.

---

## Glossary — English ↔ Arabic

| English | Arabic / meaning |
|---|---|
| Microcontroller (MCU) | متحكم دقيق |
| Firmware | البرنامج اللي شغال على الجهاز |
| Bare-metal | شغال بدون OS عام |
| Register | سجل Hardware / CPU |
| GPIO | مدخل/مخرج رقمي عام |
| Peripheral | وحدة طرفية Hardware (UART, ADC, Timer...) |
| Toolchain | أدوات التحويل والبناء والتحميل |
| Compiler | مترجم C |
| Linker | رابط object files والـ sections |
| Debugger | أداة تتبع الأخطاء |
| Flash | ذاكرة غير متطايرة للبرنامج/البيانات الدائمة |
| RAM | ذاكرة تشغيل قابلة للكتابة |
| Stack | منطقة مرتبطة بـ function calls/automatic storage |
| Heap | Dynamic allocation region |
| Declaration | إعلان وجود الاسم ونوعه |
| Definition | تعريف object / function فعليًا |
| Scope | نطاق ظهور الاسم |
| Lifetime | مدة بقاء الـ object |
| Implicit cast/conversion | تحويل نوع تلقائي |
| Explicit cast | تحويل نوع مكتوب في الكود |
| Truncation | فقد جزء من القيمة أو الـbits |
| Overflow | تجاوز المجال المسموح |
| Bitmask | قيمة bits لتحديد/تغيير bits معينة |
| Operand | مدخل أو طرف العملية |
| Operator | رمز العملية |
| Precedence | أولوية ربط العمليات |
| Associativity | اتجاه التجميع عند نفس الأولوية |
| Iteration | دورة من loop |
| Fall-through | الانتقال لتنفيذ الـ case التالية بلا `break` |
| Interrupt | حدث يوقف التسلسل العادي مؤقتًا لخدمة عاجلة |
| DMA | Direct Memory Access: نقل بيانات بمساعدة hardware بدون CPU copy لكل byte |

---

