
---

## Study Map — خريطة المذاكرة

| Part | Topic                                                                                       |
| ---- | ------------------------------------------------------------------------------------------- |
| 1    | [[#Part 1 — Structures Fundamentals\|Struct Basics & Initialization]]                       |
| 2    | [[#Part 2 — Nested and Self-Referential Structures\|Nested / Self-Referential Structures]]  |
| 3    | [[#Part 3 — Structure Alignment Padding and Packing\|Alignment, Padding & Packing]]         |
| 4    | [[#Part 4 — typedef with Structures\|typedef]]                                              |
| 5    | [[#Part 5 — Structures with Pointers Arrays and Dynamic Memory\|Pointers, Arrays & malloc]] |
| 6    | [[#Part 6 — Linked Lists and Self-Referential Nodes\|Linked List]]                          |
| 7    | [[#Part 7 — Structures and Functions\|Structs & Functions]]                                 |
| 8    | [[#Part 8 — Bit Fields\|Bit Fields]]                                                        |
| 9    | [[#Part 9 — Unions and Tagged Unions\|Union & Tagged Union]]                                |
| 10   | [[#Part 10 — Anonymous Structures and Unions\|Anonymous Struct / Union]]                    |
| 11   | [[#Part 11 — Enumeration enum\|Enums]]                                                      |
| 12   | [[#Part 12 — Lab 5\|Lab 5 + Guided Solutions]]                                              |
| 13   | [[#Part 13 — Quick Revision and Practice\|Revision & Questions]]                            |

---

## Part 1 — Structures Fundamentals


### يعني إيه `struct`؟

أحيانًا عايز تمثّل **حاجة واحدة** ليها أكتر من خاصية، وكل خاصية نوعها مختلف. مثلًا كتاب ليه:

- `title`: اسم الكتاب — نص.
- `author`: اسم المؤلف — نص.
- `price`: سعر الكتاب — رقم عشري.
- `pages`: عدد الصفحات — رقم صحيح.

من غير `struct` ممكن تعمل أربع متغيرات متفرقة. لكن لو عندك 100 كتاب، هتبدأ تتوه في العلاقة بين البيانات. هنا فكرة الـ**Structure**: نجمع خصائص كيان واحد تحت نوع بيانات جديد.

```c
struct Book {
    char title[50];
    char author[50];
    double price;
    int pages;
};
```

`Book` هنا اسمه **Structure Tag**، و`title` و`author` و`price` و`pages` اسمهم **Members / Fields**.

**الـSyntax العام:**

```c
struct StructureName {
    data_type member1;
    data_type member2;
    // ...
};
```

> [!important] مهم جدًا
> الـ`struct` بتسمح إن **الـMembers يكونوا بأنواع مختلفة**، بعكس الـ`array` اللي عناصرها من نفس النوع.
>
> تعريف شكل النوع `struct Book { ... };` **مش معناه إنك أنشأت كتابًا فعلًا**. إنت كده عرّفت القالب. حجز مساحة لكائن من النوع ده بيحصل لما تعرّف Variable منه.

### Struct Type vs Struct Object

```c
struct Book {                 // تعريف نوع / قالب
    char title[50];
    double price;
    int pages;
};

struct Book book1;           // كائن من النوع Book
struct Book book2;           // كائن تاني مستقل
```

| التعبير | معناه |
|---|---|
| `struct Book` | اسم نوع بيانات مركّب |
| `book1` | Object / Variable من النوع ده |
| `book1.price` | الوصول لعضو `price` داخل `book1` |
| `sizeof(struct Book)` | الحجم الكلي لكائن واحد من النوع ده (شامل Padding محتمل) |

> [!note] Memory nuance
> الـObject ممكن يكون Local أو Global أو Dynamically Allocated، ومكان وجوده بيعتمد على **Storage Duration** وطريقة إنشائه. جملة «التعريف يحجز ذاكرة» مقصود بيها تعريف الكائن، مش مجرد إعلان نوع الـ`struct`.

### Member Access باستخدام الـDot `.`

```c
#include <stdio.h>

struct Sensor {
    int id;
    float temperature;
};

int main(void) {
    struct Sensor s1 = {7, 26.5f};

    printf("ID = %d\n", s1.id);
    printf("Temperature = %.1f\n", s1.temperature);
    return 0;
}
```

**Output:**

```text
ID = 7
Temperature = 26.5
```

الـ`.` معناها: «هات العضو ده **من الـObject نفسه**».

### Struct Initialization — التهيئة

**1. Initialization بترتيب الأعضاء (Positional):**

```c
struct Book book1 = {"C How to Program", "Deitel", 100.0, 200};
```

الترتيب لازم يمشي بنفس ترتيب الـFields المكتوبة في الـStructure Definition.

**2. Designated Initializers (من C99):**

```c
struct Book book2 = {
    .title = "Embedded C",
    .author = "Instructor",
    .pages = 180,
    .price = 125.5
};
```

دي أوضح، لأن كل قيمة مكتوب جنبها اسم العضو المقصود، ومش محتاج تلتزم بنفس الترتيب.

**3. Partial Initialization:**

```c
struct Sensor s = {.id = 10};
// s.temperature = 0.0f
```

بقية الأعضاء اللي مش حددتها بيتم تهيئتها للصفر المناسب لنوعها. لكن **متغير محلي عادي من غير أي Initialization** مش مضمون يكون صفر.

**4. تعديل الـMembers بعد الإنشاء:**

```c
book1.price = 150.0;
book1.pages = 250;
```

بالنسبة للـ`char title[50]`، مينفعش تعمل `book1.title = "New";` لأن الـArray مش قابلة للإسناد مباشرة. استخدم `snprintf` أو نسخ آمن مع التأكد من السعة:

```c
#include <stdio.h>
snprintf(book1.title, sizeof book1.title, "%s", "New title");
```

### Struct Assignment (نسخ كائن كامل)

```c
struct Sensor a = {1, 27.0f};
struct Sensor b = a;  // Copy of members
b.id = 99;
```

هنا `a.id` لسه `1`، لأن `b` نسخة مستقلة. **لكن** لو الـStruct فيها Pointer، اللي بيتنسخ هو **العنوان**، مش البيانات الموجودة على الـHeap وراه؛ وده اسمه **Shallow Copy**.

> [!tip] Embedded example
> `struct SensorReading { uint16_t adc; float voltage; uint8_t valid; };` ينفع تمثّل قراءة Sensor واحدة بكل البيانات المرتبطة بيها، بدل متغيرات منفصلة.

---

## Part 2 — Nested and Self-Referential Structures


### Structure جوّه Structure — Nested Struct

طبيعي إن الـStruct يبقى فيه **Struct تاني**، بشرط يكون النوع الداخلي معروف ومكتمل وقت استخدامه **بالقيمة**.

```c
#include <stdio.h>

struct Address {
    char city[20];
    int zip;
};

struct Person {
    char name[50];
    struct Address addr;
};

int main(void) {
    struct Person p = {"Ali", {"Cairo", 11511}};
    printf("%s lives in %s\n", p.name, p.addr.city);
    return 0;
}
```

**Output:** `Ali lives in Cairo`

لاحظ طريقة الوصول: `p.addr.city` = `city` جوّه `addr` اللي جوّه `p`.

### هل Struct ينفع تحتوي نسخة من نفسها؟

**لأ، مش بالقيمة مباشرةً.**

```c
struct Node {
    int data;
    struct Node next;  // ERROR: incomplete / infinitely nested type
};
```

فكر فيها: عشان تعرف حجم `Node` محتاج تعرف حجم `next`، و`next` نفسه جوّاه `next` تاني، وهكذا بلا نهاية. الـCompiler مش قادر يطلع حجم نهائي.

### الحل: Self-Reference through Pointer

```c
struct Node {
    int data;
    struct Node *next;  // Valid
};
```

الـ`next` **مش Node كاملة**؛ ده Pointer بيخزّن عنوان Node تانية. حجم الـPointer معروف على الـTarget حتى لو حجم الـNode لسه بيتحدد.

```text
Node A                        Node B
+-----------+                 +-----------+
| data = 10 |                 | data = 20 |
| next -----+---------------->| next=NULL |
+-----------+                 +-----------+
```

> [!important] فرّق بين الاتنين
> `struct Node next;` = كائن `Node` كامل داخل كائن `Node` — غير مسموح.
>
> `struct Node *next;` = عنوان لعقدة تانية — مسموح، والأساس في Linked Lists وTrees.

### Indirect Self-Reference — المرجعية الدائرية غير المباشرة

حتى لو نوعين مختلفين، مينفعش كل واحد يحتوي التاني **بالقيمة** في سلسلة دائرية:

```c
/* Conceptually invalid: no finite size and incomplete types */
struct B;
struct A { struct B b; }; // B is incomplete here
struct B { struct A a; };
```

لكن ينفع تمسك **Pointer** للنوع الآخر:

```c
struct B;                  // Forward declaration

struct A {
    struct B *b;
};

struct B {
    struct A *a;
};
```

لأننا محتاجين حجم الـPointer بس، ومش محتاجين الحجم الكامل للنوع المشار إليه عند إعلان العضو.

### Forward Declaration vs Complete Definition

```c
struct Device;              // Incomplete type — name is known
struct Device *p = 0;       // Pointer to incomplete type is valid

struct Device {             // Complete type
    int id;
};
```

> [!warning] نقطة امتحان
> تقدر تعرّف **Pointer** لـIncomplete Struct، لكن لا يمكنك عمل Object منه أو استخدام `sizeof(struct Device)` قبل اكتمال تعريفه.

---

## Part 3 — Structure Alignment Padding and Packing



دي من أهم النقاط في **Embedded C** لأنك بتفكر في **RAM، بروتوكولات الـCommunication، وترتيب البيانات بالـBytes**.

### 1. Alignment — محاذاة البيانات

معظم المعالجات بتفضّل — وأحيانًا بتشترط — إن أنواع معينة تبدأ من عناوين متوافقة مع **Alignment Requirement** بتاعتها.

**مثال شائع على منصة معينة:**

- `char`: محاذاة 1 byte.
- `uint16_t`: محاذاة 2 bytes.
- `uint32_t`: محاذاة 4 bytes.
- `double`: ممكن محاذاة 8 bytes على بعض المنصات.

> [!note] مش قواعد عالمية
> القيم دي **مثال شائع**، وممكن تختلف حسب الـMCU والـABI والـCompiler. حجم النوع **مش لازم يساوي** شرط محاذاته دائمًا.

### 2. Padding — فراغات بيضيفها الـCompiler

شوف المثال الموجود في رسمة **Slide 147**:

```c
#include <stdint.h>

struct Foo {
    char a;
    uint16_t b;
    int32_t c;
    char d;
};
```

لو افترضنا إن الـAlignment زي المثال فوق، الترتيب المتوقع:

```text
Offset     0     1     2     3     4     5     6     7     8     9    10    11
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
Members  |  a  | PAD |     b     |           c           |  d  |     PAD       |
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
```

الشرح خطوة بخطوة:

1. `a` بياخد Byte واحد عند Offset `0`.
2. `b` غالبًا عايز يبدأ عند Offset قابل للقسمة على `2`، فبيتم إضافة Byte Padding عند `1`.
3. `b` بياخد Offset `2–3`.
4. `c` بياخد Offset `4–7` لأنه 4 Bytes.
5. `d` بياخد Offset `8`.
6. بيتم إضافة **Tail Padding** عند `9–11` عشان الحجم الكلي يكون مناسب لعمل **Array of Foo** مع محاذاة كل عنصر.

**الحجم الإجمالي المتوقع في المثال: 12 Bytes، رغم إن مجموع أحجام الأعضاء = 8 Bytes.**

### 3. ترتيب الأعضاء يفرق جدًا

```c
struct BetterFoo {
    int32_t c;
    uint16_t b;
    char a;
    char d;
};
```

نفس الأعضاء، لكن بعد إعادة ترتيبهم:

```text
Offset     0     1     2     3     4     5     6     7
         +-----------------------+-----------+-----+-----+
Members  |           c           |     b     |  a  |  d  |
         +-----------------------+-----------+-----+-----+
```

في نفس افتراضات الـTarget: **8 Bytes بدل 12**.

| Object | Sum of member sizes | Possible `sizeof` on the assumed target |
|---|---:|---:|
| `struct Foo` | 8 | 12 |
| `struct BetterFoo` | 8 | 8 |

> [!tip] Embedded Optimization
> إعادة ترتيب الـMembers بحسب متطلبات الـAlignment ممكن تقلّل استهلاك RAM، **لكن مش تغيّر ترتيبهم عشوائيًا** لو فيه Binary Format أو ABI بتعتمد على ترتيب موجود.

### 4. إزاي تعرف الحجم الحقيقي عندك؟

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct Foo {
    char a;
    uint16_t b;
    int32_t c;
    char d;
};

int main(void) {
    printf("sizeof(Foo) = %zu\n", sizeof(struct Foo));
    printf("a offset = %zu\n", offsetof(struct Foo, a));
    printf("b offset = %zu\n", offsetof(struct Foo, b));
    printf("c offset = %zu\n", offsetof(struct Foo, c));
    printf("d offset = %zu\n", offsetof(struct Foo, d));
    return 0;
}
```

`offsetof` بتحدد Offset العضو من بداية الـStruct. شغّل ده على **نفس الـCompiler/Target** اللي هتشتغل عليه، مش على PC وخلاص.

### 5. Packing — تقليل الـPadding

السلايد 148 بتشرح إنك ممكن تطلب من الـCompiler إنه يخزّن الأعضاء متراصّة قدر الإمكان:

```c
#pragma pack(push, 1)
struct PackedPacket {
    char type;
    uint32_t value;
};
#pragma pack(pop)
```

على Compiler بيدعم الأسلوب ده، الحجم غالبًا يبقى `5` بدل `8` Bytes بافتراض `uint32_t` = 4 Bytes.

لكن لازم تعرف:

- `#pragma pack` **مش جزء محمول من Standard C**؛ التفاصيل بتختلف حسب الـCompiler.
- قراءة عضو متعدد البايتات من عنوان غير محاذٍ ممكن تبقى **أبطأ** أو تحتاج تعليمات إضافية أو تعمل Alignment Fault على بعض المعالجات.
- الـPacking **مش بيحدد Endianness**؛ ترتيب البايتات في البروتوكول لازم يتحدد بوضوح.
- لكتابة Network Packets أو Hardware Formats، أحيانًا الأفضل تبني الـBytes صراحة بدل ما تفترض Layout Struct مباشر.

**مثال أكثر قابلية للنقل لتخزين قيمة 16-bit بترتيب محدد:**

```c
#include <stdint.h>

void encode_u16_be(uint8_t out[2], uint16_t x) {
    out[0] = (uint8_t)(x >> 8);
    out[1] = (uint8_t)x;
}
```

لو `x = 0x1234`، هيكون `out[0] = 0x12` و`out[1] = 0x34` بغض النظر عن Endianness الداخلية للـMCU.

> [!warning] Exam / Interview
> سؤال: ليه `sizeof(struct)` أكبر من مجموع الـMembers؟
>
> **Padding + Alignment**، وأحيانًا **Tail Padding**. الحجم النهائي **Implementation-dependent**.

---

## Part 4 — typedef with Structures


### `typedef` بيعمل إيه؟

الـ`typedef` بيعمل **Alias / اسم بديل** لنوع موجود. **مش بيخلق Type منفصل جديد بخصائص مختلفة**.

```c
typedef unsigned int uint_alias;
uint_alias x = 10;
```

الاتنين `uint_alias` و`unsigned int` نفس النوع هنا.

### Struct without typedef

```c
struct Sensor {
    int id;
    float value;
};

struct Sensor s1;
```

### Struct with typedef — الطريقة الأولى

```c
typedef struct {
    int id;
    float value;
} Sensor;

Sensor s1;
```

لاحظ إن الـStruct هنا **من غير Tag**؛ الاسم `Sensor` هو الـAlias اللي عملناه.

### Named Struct + typedef — الطريقة التانية

```c
struct Book {
    char title[50];
    double price;
};

typedef struct Book Book_t;

struct Book a;
Book_t b;
```

الاتنين `a` و`b` من نفس الـStruct Type.

### من السلايد — مثال Book

```c
struct Book {
    char title[50];
    char author[50];
    int pages;
    float price;
};

typedef struct Book Book_t;
```

> [!important] متخلطش بينهم
> - `struct Book` اسمه **Struct Tag**.
> - `Book_t` اسمه **Typedef Alias**.
> - `typedef` مش بيحجز Memory لوحده.
> - لو هتعمل Self-Referential Struct، غالبًا الأسهل تستخدم **Named Struct**.

---

## Part 5 — Structures with Pointers Arrays and Dynamic Memory


### 1. Dot `.` vs Arrow `->`

لو معاك **Struct Object** استخدم `.`، ولو معاك **Pointer to Struct** استخدم `->`.

```c
#include <stdio.h>

struct Person {
    char name[50];
    int age;
};

int main(void) {
    struct Person p1 = {"Alice", 30};
    struct Person *ptr = &p1;

    printf("%s\n", p1.name);        // Dot: object
    printf("%s\n", (*ptr).name);    // Dereference, then dot
    printf("%s\n", ptr->name);      // Arrow: preferred
    return 0;
}
```

**Output:** ثلاث مرات `Alice`.

**القانون الأساسي:**

```c
ptr->age == (*ptr).age
```

`(*ptr).age` محتاجة أقواس، لأن الـ`.` أولوّيته أعلى من الـ`*`.

### 2. Memory picture

```text
p1 object (say address 0x2000)               ptr pointer
+-------------------+                  +-------------------+
| name = "Alice"    | <----------------| stores 0x2000     |
| age = 30          |                  +-------------------+
+-------------------+

p1.age        -> 30
ptr           -> address of p1
ptr->age      -> 30
(*ptr).age    -> 30
```

العناوين هنا للتوضيح مش عناوين ثابتة.

### 3. Dynamic Structure Allocation (`malloc`)

السلايد 151 بتستخدم `malloc()` لإنشاء كائن أثناء التشغيل.

```c
#include <stdio.h>
#include <stdlib.h>

struct Person {
    char name[50];
    int age;
};

int main(void) {
    struct Person *p = malloc(sizeof *p);
    if (p == NULL) {
        puts("Allocation failed");
        return 1;
    }

    snprintf(p->name, sizeof p->name, "%s", "Bob");
    p->age = 45;

    printf("%s is %d\n", p->name, p->age);
    free(p);
    p = NULL;
    return 0;
}
```

**Output:** `Bob is 45`

**تتبّع الخطوات:**

1. `sizeof *p` يجيب حجم كائن `struct Person`، مش حجم Pointer.
2. `malloc` يرجع عنوان مساحة تكفي للكائن، أو `NULL` لو فشل.
3. `p->name` و`p->age` للوصول للأعضاء عن طريق العنوان.
4. `free(p)` لتحرير المساحة اللي حجزتها.
5. بعد `free` مينفعش تستخدم `p->age`؛ ده **Use-After-Free**.

> [!warning] Embedded reality
> كتير من مشاريع **Bare-metal** بتقلّل أو بتمنع استخدام `malloc` بسبب Limited RAM وFragmentation وصعوبة التنبؤ بوقت التنفيذ. استخدم Static Buffers / Pools لما التصميم محتاج سلوك ثابت، لكن افهم `malloc` لأنها موجودة في المحاضرة.

### 4. Pointer to first element in Array of Structs — Slide 152

```c
#include <stdio.h>

struct Person {
    char name[20];
    int age;
};

int main(void) {
    struct Person group[3] = {
        {"Tom", 25},
        {"Jerry", 28},
        {"Spike", 35}
    };

    struct Person *ptr = group;

    for (size_t i = 0; i < 3; i++) {
        printf("%s: %d\n", (ptr + i)->name, (ptr + i)->age);
    }
    return 0;
}
```

**Output:**

```text
Tom: 25
Jerry: 28
Spike: 35
```

ليه `(ptr + i)` بيقفز كائن كامل؟ لأن نوع `ptr` هو `struct Person *`، فالـPointer Arithmetic بتحرّكه بمقدار `i * sizeof(struct Person)`.

### 5. Passing a Struct Pointer to a Function

```c
#include <stdio.h>

struct Person { char name[20]; int age; };

void printPerson(const struct Person *p) {
    printf("Name: %s, Age: %d\n", p->name, p->age);
}

int main(void) {
    struct Person person = {"Sarah", 40};
    printPerson(&person);
    return 0;
}
```

`const` هنا معناها الدالة **مش مفروض تعدّل محتوى الـObject من خلال الـPointer ده**.

### 6. Array of Structs vs Struct of Arrays

**Array of Structs:** كل عنصر هو كائن كامل:

```c
struct Reading {
    int sensor_id;
    float value;
};

struct Reading readings[3] = {
    {1, 24.5f}, {2, 26.0f}, {3, 25.2f}
};

printf("%.1f\n", readings[1].value);  // 26.0
```

**Struct containing Arrays:** كائن واحد جواه Arrays:

```c
struct History {
    int ids[3];
    float values[3];
};
```

| Form | Example | Access |
|---|---|---|
| Array of Structs | `struct Reading readings[3]` | `readings[i].value` |
| Struct of Arrays | `struct History h` | `h.values[i]` |

### 7. Books Array — Slide 153

```c
#include <stdio.h>

typedef struct {
    char title[20];
    double price;
    int pages;
} Book;

int main(void) {
    Book books[3] = {
        {"Learn C", 650.50, 325},
        {"C Pointers", 175.00, 225},
        {"C Pearls", 250.00, 325}
    };

    for (size_t i = 0; i < 3; ++i) {
        printf("Title: %s | Price: %.2f | Pages: %d\n",
               books[i].title, books[i].price, books[i].pages);
    }
    return 0;
}
```

**الفكرة:** كل كتاب اتخزّن كـStruct مستقل داخل Array، والـ`for` بتمر على كل الكتب. استخدمنا Initialization مباشرة بدل تكرار `strcpy`، لكن المثال بيشرح نفس فكرة السلايد.

---

## Part 6 — Linked Lists and Self-Referential Nodes


### يعني إيه Linked List؟

الـ**Linked List** عبارة عن Nodes، وكل Node فيها:

1. **Data** — القيمة اللي عايز تخزنها.
2. **Link / Next Pointer** — عنوان الـNode اللي بعدها.

```c
struct Node {
    int data;
    struct Node *next;
};
```

رسمة Slide 155 معناها:

```text
head
 |
 v
+------------+      +------------+
| data = 10  |      | data = 20  |
| next ------+----->| next=NULL  |
+------------+      +------------+
```

**الفرق عن Array:** الـNodes مش لازم تكون جنب بعض في الذاكرة. الربط بينها بيحصل بالعناوين. بعكس الـArray اللي عناصرها متجاورة في Memory.

### Complete Example — عقدتين مع فحص `malloc`

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main(void) {
    struct Node *head = malloc(sizeof *head);
    if (head == NULL) return 1;

    struct Node *second = malloc(sizeof *second);
    if (second == NULL) {
        free(head);
        return 1;
    }

    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = NULL;

    for (struct Node *current = head;
         current != NULL;
         current = current->next) {
        printf("%d\n", current->data);
    }

    free(second);
    free(head);
    return 0;
}
```

**Output:**

```text
10
20
```

**تتبّع مهم:**

- `head` عنوان أول عقدة.
- `head->next` عنوان العقدة التانية.
- `head->next->data` = `20`.
- `second->next = NULL` علامة إن مفيش عقدة بعد كده.
- `current = current->next` ينقلك للعقدة اللي بعدها.

> [!warning] Common mistakes
> - Dereferencing `NULL`: مينفعش تعمل `head->data` لو `head == NULL`.
> - **Memory Leak:** تنسى `free`.
> - **Dangling Pointer:** تستخدم عقدة بعد `free`.
> - تفقد `head` قبل ما تحفظ مكان أول عقدة.

### Why self-referential structures matter

نفس الفكرة موجودة في **Trees، Stacks، Queues** وData Structures كتير. الاختلاف بيكون في عدد الـPointers وطريقة ترتيب الـNodes.

---

## Part 7 — Structures and Functions


### 1. Pass an Individual Member — Slide 156

تقدر تبعت عضو واحد زي ما بتبعت أي Variable.

```c
#include <stdio.h>

struct Book {
    char title[50];
    double price;
};

void printPrice(double p) {
    printf("Price: %.2f\n", p);
}

int main(void) {
    struct Book b = {"C Programming", 199.99};
    printPrice(b.price);
    return 0;
}
```

**Output:** `Price: 199.99`

`b.price` متغير نوعه `double`، فالدالة مش محتاجة تعرف إن القيمة جاية من Struct.

### 2. Pass a Whole Struct by Value — Slide 157

```c
#include <stdio.h>

struct Book {
    char title[50];
    double price;
};

void setFree(struct Book b) {
    b.price = 0.0;          // بيعدّل النسخة المحلية فقط
}

int main(void) {
    struct Book book = {"Learn C", 200.0};
    setFree(book);
    printf("%.1f\n", book.price);
    return 0;
}
```

**Output:** `200.0`

لأن الباراميتر `b` نسخة جديدة من `book`. تعديلها مش بيوصل للـObject الأصلي.

### 3. Pass by Pointer / Address — Slide 158

```c
#include <stdio.h>

struct Book { char title[50]; double price; };

void setFree(struct Book *b) {
    b->price = 0.0;
}

int main(void) {
    struct Book book = {"Learn C", 200.0};
    setFree(&book);
    printf("%.1f\n", book.price);
    return 0;
}
```

**Output:** `0.0`

أرسلنا **عنوان** الكائن، فالدالة قدرت تعدّل الأصل من خلاله.

> [!important] دقة في C
> حتى لما بنقول **Pass by Reference** في الشرح، لغة C تقنيًا بتمرّر **Pointer by Value**. قيمة الـPointer (العنوان) هي اللي بتتنسخ، لكن العنوان بيشاور على نفس الكائن الأصلي.

### مقارنة مهمة

| Form | Function parameter | Copy of data? | Can modify original? |
|---|---|---|---|
| Single member | `double x` | نسخة من العضو | لا |
| Struct by value | `struct Book b` | نسخة من الكائن | لا، إلا تأثيرات غير مباشرة عبر Pointers بداخلها |
| Struct by pointer | `struct Book *b` | نسخة من عنوان الكائن | نعم باستخدام `b->member` |
| Read-only pointer | `const struct Book *b` | نسخة من العنوان | لا عبر الـPointer ده |

**ليه الـPointer ممكن يبقى اختيار أفضل؟** لو الـStruct كبيرة، مش بتنسخ كل محتواها مع كل Call. لكن المقابل إنك لازم تحافظ على صحة الـPointer وعمر الكائن.

### 4. Return a Struct by Value — Slides 159–160

```c
#include <stdio.h>

struct Book {
    char title[50];
    double price;
};

struct Book createBook(void) {
    struct Book b = {"Clean Code", 150.75};
    return b;
}

int main(void) {
    struct Book myBook = createBook();
    printf("%s: %.2f\n", myBook.title, myBook.price);
    return 0;
}
```

**Output:** `Clean Code: 150.75`

ده **صحيح وآمن في C**: الدالة بترجع **قيمة الكائن**؛ مش بترجع عنوان متغير محلي انتهى عمره.

**ملحوظة RVO:** السلايد بتشرح إن Compiler حديث **ممكن** يلغي النسخ الإضافي باستخدام Return Value Optimization أو أساليب مشابهة. لكن **صحة الكود لا تعتمد على حدوث Optimization**، وC مش بتضمن إن ده هيحصل في كل الظروف. لو الأداء/الذاكرة مهمين جدًا، اقس بنفسك على الـToolchain بتاعك.

### 5. Safe Return vs Dangerous Return — Slide 161

**مسموح:**

```c
struct Book makeBook(void) {
    struct Book temp = {"Embedded C", 99.0};
    return temp;   // Safe: return by value
}
```

**خطر جدًا:**

```c
struct Book *wrong(void) {
    struct Book temp = {"Embedded C", 99.0};
    return &temp;  // WRONG: pointer to dead local variable
}
```

المتغير `temp` عمره بينتهي بعد خروج الدالة؛ استخدام الـPointer المرجع ليه **Undefined Behavior**.

**الـStatic Local خيار مختلف:**

```c
struct Book *getSharedBook(void) {
    static struct Book b = {"Shared", 123.0};
    return &b;  // Lifetime continues for the whole program
}
```

دي صحيحة من ناحية Lifetime، لكن فيها مشاكل تصميم محتملة: نفس الـObject بيتشارك بين كل المستدعين، وممكن استدعاء تاني يغيّر البيانات. الوصول المتزامن من أكتر من Task/Thread يحتاج Synchronization مناسب.

### 6. Return a Dynamically Allocated Struct Pointer — Slides 162–163

```c
#include <stdio.h>
#include <stdlib.h>

struct Book {
    char title[50];
    double price;
};

struct Book *createBook(void) {
    struct Book *p = malloc(sizeof *p);
    if (p == NULL) return NULL;

    snprintf(p->title, sizeof p->title, "%s", "Effective C");
    p->price = 220.0;
    return p;
}

int main(void) {
    struct Book *book = createBook();
    if (book == NULL) return 1;

    printf("%s: %.2f\n", book->title, book->price);
    free(book);
    return 0;
}
```

**Output:** `Effective C: 220.00`

**متى تستخدم إيه؟**

| Return type | Lifetime | Who owns memory? |
|---|---|---|
| `struct Book` | نسخة صحيحة بيرجع بيها الكائن | Caller بيستقبل القيمة |
| `struct Book *` to `static` | طوال البرنامج | غالبًا الدالة؛ Caller **مايعملش `free`** |
| `struct Book *` from `malloc` | لحد `free` | لازم يكون فيه اتفاق واضح: Caller غالبًا مسؤول عن `free` |
| `struct Book *` to local auto var | انتهى بعد Return | **خطأ** |

### 7. Function Pointers inside Structs — Slides 164–165

الـC مش بتسمح إنك تعرّف **Function Body جوّه Struct** بالطريقة الموجودة في لغات OOP، لكن ينفع تحتفظ بـ**Pointer to Function** كعضو.

```c
#include <stdio.h>

void printDetails(const char *name, int age) {
    printf("Name: %s, Age: %d\n", name, age);
}

struct Person {
    char name[50];
    int age;
    void (*print)(const char *, int);
};

int main(void) {
    struct Person p = {"Alice", 30, printDetails};
    p.print(p.name, p.age);
    return 0;
}
```

**إزاي تقرأ `void (*print)(const char *, int);`؟**

- `print` عبارة عن **Function Pointer**.
- بتشاور على دالة بتستقبل `const char *` و`int`.
- الدالة بترجع `void`.

### Function Pointer Table — Slide 165

```c
#include <stdio.h>

struct Operation {
    char symbol;
    int (*operate)(int, int);
};

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    struct Operation ops[2] = {
        {'+', add},
        {'*', mul}
    };

    printf("3 + 4 = %d\n", ops[0].operate(3, 4));
    printf("3 * 4 = %d\n", ops[1].operate(3, 4));
    return 0;
}
```

**Output:**

```text
3 + 4 = 7
3 * 4 = 12
```

دي فكرة شبيهة بـ**Callback Table / Dispatch Table**: تختار السلوك حسب الدالة المخزنة في الـStruct. في Embedded ممكن تستخدمها في **Drivers / Interfaces / Command Handlers**.

---

## Part 8 — Bit Fields


### يعني إيه Bit Field؟

الـ`Bit-Field` عضو داخل Struct بتحطله **عرض محدد بعدد Bits** باستخدام `:`. ده مفيد لما الحالات محتاجة Bits قليلة بدل متغير Integer كامل لكل حالة.

**Syntax:**

```c
struct Flags {
    unsigned int isVisible : 1;
    unsigned int isEnabled : 1;
    unsigned int mode      : 2;
};
```

المعنى المنطقي:

- `isVisible` بياخد قيمة `0` أو `1`.
- `isEnabled` بياخد قيمة `0` أو `1`.
- `mode` (2 bits) بياخد قيمة من `0` لـ`3`.

مجموع **عرض البيانات المعرّف = 4 Bits**، لكن ده **مش معناه إن `sizeof(struct Flags)` = نصف Byte**. الـCompiler ممكن يحجز **Storage Unit** أكبر، زي 4 Bytes.

> [!warning] دقة في السلايد 166
> عبارة «uses only 4 bits total» تخص **مجموع عروض الـFields المنطقية**؛ مش الحجم النهائي اللي بيرجعه `sizeof`. الـStorage/Alignment وBit Placement **Implementation-dependent**.

### Example 1 — Slide 167

```c
#include <stdio.h>

struct Flags {
    unsigned int isVisible : 1;
    unsigned int isEnabled : 1;
    unsigned int mode      : 2;
};

struct Flags1 {
    unsigned int isVisible;
    unsigned int isEnabled;
    unsigned int mode;
};

int main(void) {
    struct Flags f = {1, 0, 2};
    struct Flags1 normal = {1, 0, 2};

    printf("Fields: %u %u %u\n", (unsigned)f.isVisible, (unsigned)f.isEnabled, (unsigned)f.mode);
    printf("Packed struct sizeof = %zu\n", sizeof f);
    printf("Ordinary struct sizeof = %zu\n", sizeof normal);
    return 0;
}
```

**Output المتوقع في منصة السلايد:**

```text
Fields: 1 0 2
Packed struct sizeof = 4
Ordinary struct sizeof = 12
```

مش لازم تطلع نفس أحجام السلايد عند كل Compiler.

### Example 2 — Overflow in an Unsigned Bit-Field (Slide 168)

```c
#include <stdio.h>

struct {
    unsigned int age : 3;
} Age;

int main(void) {
    Age.age = 4;
    printf("%u\n", (unsigned)Age.age);  // 4

    Age.age = 7;
    printf("%u\n", (unsigned)Age.age);  // 7

    Age.age = 8;
    printf("%u\n", (unsigned)Age.age);  // 0 (unsigned 3-bit)
    return 0;
}
```

**ليه `8` بتبقى `0`؟**

```text
3 bits maximum: 111₂ = 7
8 in binary   : 1000₂
Low 3 bits    :  000₂ = 0
```

الـUnsigned Bit-Field بتستقبل نتيجة تحويل لمدى الـ3 Bits (Modulo `2^3`). على الجانب التاني **Signed Bit-Fields** وحالات Overflow دي لازم تتعامل معاها بحذر، لأن النتائج ممكن تبقى Implementation-defined حسب النوع والـCompiler. السلايد وصفت المثال `8` بأنه Undefined Behavior، لكن **مع الحقل unsigned 3-bit النتيجة `0` محددة بقواعد التحويل لـUnsigned**؛ مش Undefined Behavior بالشكل المكتوب في التعليق.

### Bit-Fields and Hardware Registers

مثال منطقي لحقل Control Register عرضه 8 Bits:

```text
Bit:    7  6  5  4  3  2  1  0
        +--------------+------+---+
Meaning | reserved     | mode | en|
        +--------------+------+---+
```

**منطقيًا** ممكن تعرضه كـBit Fields، لكن متفترضش إن أول Bit-Field متعرّفة هتروح للـLSB على كل Platform: **ترتيب توزيع الـBits داخل Storage Unit Implementation-defined**. للوصول لهاردوير حقيقي، استخدم Bit Masks وRegister Definitions المتوافقة مع الـMCU Datasheet.

**Portable-ish mask example for a normal 8-bit variable:**

```c
#include <stdint.h>

#define ENABLE_MASK  (1u << 0)
#define MODE_MASK    (3u << 1)

void configure(uint8_t *reg, uint8_t mode) {
    *reg = (uint8_t)((*reg & ~(uint8_t)MODE_MASK) |
                     (((unsigned)mode & 3u) << 1));
    *reg = (uint8_t)(*reg | ENABLE_MASK);
}
```

> [!important] Bit-Field Limitations
> - مينفعش تاخد عنوان Bit-Field باستخدام `&object.field`.
> - مينفعش تستخدم `sizeof(object.field)` عليها مباشرة.
> - الـBit ordering والـAllocation Units وPadding **مش Portable**.
> - مش كل Compiler بيدعم نفس أنواع الـBit-Fields أو نفس الـExtensions.
> - `volatile` قد يكون لازم للـMMIO، لكنه **لا يحل** مشاكل ترتيب الـBits أو الـAtomicity.

---

## Part 9 — Unions and Tagged Unions


### يعني إيه `union`؟

الـ`union` بتشبه الـ`struct` في الشكل، لكن **كل الـMembers بتشارك نفس مساحة التخزين**. بدل ما تحجز مساحة لكل Member، بتحجز مساحة كافية لأكبر Member (مع مراعاة Alignment وربما Padding).

```c
union Data {
    int i;
    float f;
    char str[20];
};
```

في مثال السلايد 169، الحجم **20 Bytes** على الـTarget المفترض، لأن `char str[20]` أكبر عضو ومتطلبات الـAlignment مسموحة في 20 Byte.

### Structure vs Union — Memory Picture

```c
struct MixedStruct { int i; float f; char str[20]; };
union  MixedUnion  { int i; float f; char str[20]; };
```

```text
STRUCT                                 UNION
+-----+-----+--------------------+     +--------------------+
|  i  |  f  |      str[20]       |     | i / f / str[20]    |
+-----+-----+--------------------+     +--------------------+
separate storage for all members       same storage reused by members
```

**النقطة المهمة:** الـUnion مناسبة لما الكائن هيكون **إما int أو float أو string**، مش كلهم مستقلين في نفس الوقت.

### Reading and Writing Members

```c
union Data d;
d.i = 42;
// Now d.i is the intended active value.

d.f = 3.14f;
// Now d.f is the intended active value; don't assume d.i still equals 42.
```

> [!warning] Type Punning caveat
> قراءة عضو مختلف عن آخر عضو اتكتب ممكن تعتمد على **تمثيل البيانات والـCompiler**، وقد تؤدي لقيمة غير مفهومة أو حتى Trap Representation لبعض الأنواع. متستخدمش Union كطريقة عامة ومضمونة لتحويل Integer Bits لـFloat من غير فهم قواعد الـTarget.

### Tagged Union — إزاي نعرف القيمة الحالية نوعها إيه؟

سلايدز **170–173** بتجمع `enum` + `union` + `struct` علشان تعمل نوع ديناميكي بسيط اسمه **Tagged Union / Variant**.

**الفكرة:**

- الـ`enum` يحدد الـType الحالي.
- الـ`union` تمسك قيمة من الأنواع الممكنة.
- الـ`struct` تجمع الـType Tag والـValue في Object واحد.

```c
#include <stdio.h>

typedef enum {
    INTEGER,
    STRING,
    REAL,
    POINTER
} Type;

typedef struct {
    Type type;
    union {
        int integer;
        const char *string;
        float real;
        void *pointer;
    } x;
} Value;

void printValue(Value v) {
    switch (v.type) {
        case INTEGER:
            printf("Integer: %d\n", v.x.integer);
            break;
        case STRING:
            printf("String: %s\n", v.x.string);
            break;
        case REAL:
            printf("Real: %.2f\n", (double)v.x.real);
            break;
        case POINTER:
            printf("Pointer: %p\n", v.x.pointer);
            break;
        default:
            puts("Unknown type");
    }
}

int main(void) {
    Value a = {.type = INTEGER, .x.integer = 42};
    Value b = {.type = STRING,  .x.string = "Hello, union!"};
    Value c = {.type = REAL,    .x.real = 3.1415f};

    printValue(a);
    printValue(b);
    printValue(c);
    return 0;
}
```

**Output:**

```text
Integer: 42
String: Hello, union!
Real: 3.14
```

### Walkthrough

لما نكتب:

```c
Value a = {.type = INTEGER, .x.integer = 42};
```

1. `a.type = INTEGER` معناها إن القيمة المخزّنة حاليًا Integer.
2. `a.x.integer = 42` بتخزن القيمة جوّه الـUnion.
3. `printValue` بتعمل `switch(a.type)`.
4. في حالة `INTEGER` بتقرأ **نفس العضو المقصود** `a.x.integer`.

**من غير الـTag** مش هتعرف بشكل آمن أي عضو المفروض تقرأه.

### Why useful?

السلايد 173 بتذكر استخدامات الـVariant/Tagged Union في:

- **Virtual Machines** و**Interpreters**.
- **Dynamic Scripting Engines**.
- **Serialization** (تخزين/إرسال بيانات بأنواع مختلفة).

وفي Embedded ممكن تستخدمه في **Event Queues**: الـEvent له نوع (`BUTTON`, `ADC`, `UART`) والبيانات المرتبطة بالنوع بتتخزن في Union.

**مثال مختصر:**

```c
typedef enum { EVENT_BUTTON, EVENT_ADC } EventType;

typedef struct {
    EventType type;
    union {
        unsigned button_id;
        unsigned adc_value;
    } data;
} Event;
```

> [!tip] Important
> الـ`union` بتوفّر مساحة لأنك مش محتاج تحجز مساحة **كل البدائل مرة واحدة**، لكن حجم الـStruct الحاوية للـTag والـUnion ممكن يضاف له Padding.

---

## Part 10 — Anonymous Structures and Unions


### Anonymous Union — عضو من غير اسم

في C11، تقدر تحط Union **من غير Tag ومن غير اسم Member** جوّه Struct، وساعتها توصل للأعضاء الداخلية مباشرةً من الـStruct الخارجية.

```c
#include <stdio.h>

struct Data {
    int type;
    union {
        int i;
        float f;
        char str[20];
    };  // Anonymous union member
};

int main(void) {
    struct Data d = {0};
    d.type = 1;
    d.i = 42; // Direct access, NOT d.union_name.i
    printf("Type: %d, Integer: %d\n", d.type, d.i);
    return 0;
}
```

**Output:** `Type: 1, Integer: 42`

### الفرق بين Anonymous Union وNamed Union Member

```c
struct Named {
    union {
        int i;
        float f;
    } value;               // Member is called value
};

struct Anonymous {
    union {
        int i;
        float f;
    };                     // No member name
};
```

| Object | Access |
|---|---|
| `struct Named n` | `n.value.i` |
| `struct Anonymous a` | `a.i` |

> [!note] مصطلح مهم
> مجرد إن النوع **من غير Tag** مش كفاية لو عايز وصول مباشر: لازم **الـMember نفسه يكون بدون اسم** (Anonymous Member). الميزة دي متاحة قياسيًا في C11؛ بعض الـCompilers بتدعمها كـExtension قبل C11.

### Anonymous Struct — Slide 175

```c
#include <stdio.h>

struct Employee {
    int id;
    struct {
        char first[20];
        char last[20];
    };                  // Anonymous struct member
};

int main(void) {
    struct Employee emp = {0};
    emp.id = 101;
    snprintf(emp.first, sizeof emp.first, "%s", "John");
    snprintf(emp.last, sizeof emp.last, "%s", "Doe");

    printf("ID: %d, Name: %s %s\n",
           emp.id, emp.first, emp.last);
    return 0;
}
```

**Output:** `ID: 101, Name: John Doe`

بدل `emp.name.first` مثلًا، تقدر تكتب `emp.first` مباشرة.

### Register Overlay Example — Slides 172 and 176

السلايد بتعرض فكرة Union بتحتوي **Raw Register Value** و**Bit Fields** لنفس الـBits:

```c
#include <stdint.h>

typedef union {
    uint32_t value;
    struct {
        uint32_t enable   : 4;
        uint32_t mode     : 4;
        uint32_t reserved : 24;
    } bits;
} ControlRegister;

void example(void) {
    ControlRegister reg = {0};
    reg.bits.enable = 1;
    reg.bits.mode = 3;
}
```

وفي Slide 176 نسخة أقصر من المثال باستخدام **Anonymous Struct** تسمح بالكتابة `reg.enable` بدل `reg.bits.enable`.

```c
typedef union {
    uint32_t value;
    struct {
        uint32_t enable   : 1;
        uint32_t mode     : 2;
        uint32_t error    : 1;
    };  // Anonymous struct
} CONTROL_REG;
```

**ليه ده مفيد؟** عشان تعبر عن Register بشكل أسماء Fields مريحة، لكن:

> [!warning] Don't assume hardware layout
> في Register حقيقي، ترتيب الـBit Fields (مين الـLSB ومين الـMSB)، والتوافق مع الـHardware Register Width، والـCompiler ABI كلها شروط أساسية. الأمثلة دي **توضيحية من السلايد**، مش تعريفات Register جاهزة لأي MCU. استخدم الـCMSIS/Header الرسمي أو Masks حسب الـDatasheet.

---

## Part 11 — Enumeration enum


### يعني إيه Enum؟

الـ`enum` بتخليك تدي **أسماء مفهومة لثوابت صحيحة Integral Constants**، بدل ما تكتب أرقام مش واضح معناها.

```c
enum Color {
    RED,
    GREEN,
    BLUE
};
```

بشكل افتراضي:

| Enumerator | Value |
|---|---:|
| `RED` | 0 |
| `GREEN` | 1 |
| `BLUE` | 2 |

**الـEnum Type نفسه:** `enum Color`، و**Enumerators** هم `RED`, `GREEN`, `BLUE`.

### Enum Variables and Conditions — Slide 178

```c
#include <stdio.h>

enum Day {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

int main(void) {
    enum Day today = WEDNESDAY;

    if (today == WEDNESDAY) {
        puts("It's midweek.");
    }

    printf("Day index is: %d\n", (int)today);
    return 0;
}
```

**Output:**

```text
It's midweek.
Day index is: 3
```

### Custom Enum Values — Slide 179

مش لازم تبدأ من `0`، ومش لازم كل القيم تبقى متتالية:

```c
enum HttpStatus {
    OK = 200,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
};
```

وممكن تكمل من قيمة محددة:

```c
enum State {
    IDLE = 10,
    READY,      // 11
    RUNNING,    // 12
    ERROR = 20,
    STOPPED     // 21
};
```

### typedef enum — Slide 179

```c
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Priority;

Priority p = HIGH;
```

ده نفس استخدام `typedef` اللي اتعلمناه مع Struct: بدل ما تكتب `enum Priority` كل مرة، تستخدم الـAlias مباشرة.

### Practical Embedded State Machine

```c
#include <stdio.h>

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} SystemState;

void handleState(SystemState state) {
    switch (state) {
        case STATE_IDLE:
            puts("Waiting...");
            break;
        case STATE_RUNNING:
            puts("Processing...");
            break;
        case STATE_ERROR:
            puts("Error detected");
            break;
        default:
            puts("Unknown state");
            break;
    }
}
```

الـ`enum` مناسبة جدًا لتمثيل **States، Modes، Error Codes، Commands، ON/OFF options**، وده مذكور في Slide 180.

### Behind the Scenes & Limitations — Slide 180

- الـEnumerators عبارة عن **Integer Constants**.
- الـUnderlying Compatible Integer Type وحجم الـEnum بيعتمدوا على **Implementation** والمعايير/خيارات الـCompiler؛ على منصات كتير `sizeof(enum)` = `4` Bytes، **مش شرط دايمًا**.
- تقدر تعرض القيمة الرقمية باستخدام `printf("%d", (int)state)` لما القيمة في مدى `int`؛ الـCast بيخلّي المقصود واضح.
- لغة C مش بتعمل **Strong Type Safety** للـEnums بنفس صرامة بعض اللغات؛ مينفعش تعتمد على إن الـCompiler يمنع كل القيم غير الصحيحة.
- اسم الـEnum بيستخدم لزيادة **Readability** وتقليل استخدام Magic Numbers، مش كضمان ضد كل المدخلات الخاطئة.

**مثال لمشكلة Logical Invalid State:**

```c
SystemState s = (SystemState)99;  // قد يكون رقمًا غير معرف ضمن الحالات
handleState(s);                   // default catches it
```

> [!tip] سؤال مهم
> الفرق بين `enum` و`#define`؟ الـEnum بتجمع أسماء قيم مرتبطة داخل Type واحد وبتساعد في الـDebugging والـReadability؛ الـMacro مجرد Textual Replacement أثناء الـPreprocessing.

---

## Part 12 — Lab 5


السلايد الأخيرة فيها **4 تمارين**: Student، Complex Numbers، Library Management، Employee Management. هنمشي من البسيط للأكبر، مع شرح التصميم وأمثلة تنفيذ قابلة للتشغيل للتدريب.

### Task 1 — Student Management

**المطلوب في السلايد:** اعمل `struct Student` فيها `name`, `age`, `total marks`؛ استقبل بيانات طلبة، اطبع المعلومات، احسب **Average Marks**، **Highest Marks**، و**Top 3**.

#### قبل الكود: Algorithm

1. عرّف Struct لطالب واحد.
2. اعمل Array من الطلاب؛ اختار حدًا أقصى معقول.
3. اقرأ `n` وتأكد إنها ضمن الحدود.
4. اجمع `total_marks` واحسب `average = sum / n` مع مراعاة تحويل النوع لـ`double`.
5. رتّب **نسخة** من الطلاب ترتيب تنازلي بالـMarks.
6. أول عنصر بعد الترتيب هو Highest، وأول `min(n, 3)` يمثلوا Top 3.

#### Complete C Solution

```c
#include <stdio.h>

#define MAX_STUDENTS 50
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    unsigned age;
    double total_marks;
} Student;

void sortDescending(Student a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j].total_marks > a[i].total_marks) {
                Student temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int n;
    double sum = 0.0;

    printf("How many students (1-%d)? ", MAX_STUDENTS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_STUDENTS) {
        puts("Invalid count");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Student %d (name age marks): ", i + 1);
        if (scanf("%49s %u %lf",
                  students[i].name,
                  &students[i].age,
                  &students[i].total_marks) != 3) {
            puts("Invalid input");
            return 1;
        }
        sum += students[i].total_marks;
    }

    puts("\nAll students:");
    for (int i = 0; i < n; ++i) {
        printf("%s | Age: %u | Marks: %.2f\n",
               students[i].name, students[i].age,
               students[i].total_marks);
    }

    printf("\nAverage = %.2f\n", sum / n);

    sortDescending(students, n);
    printf("Highest: %s (%.2f)\n",
           students[0].name, students[0].total_marks);

    puts("Top 3:");
    int limit = (n < 3) ? n : 3;
    for (int i = 0; i < limit; ++i) {
        printf("%d) %s - %.2f\n", i + 1,
               students[i].name, students[i].total_marks);
    }
    return 0;
}
```

**Example Input:**

```text
4
Ali 20 80
Mona 19 97
Omar 21 85
Nada 20 90
```

**الأجزاء المهمة في الناتج:**

```text
Average = 88.00
Highest: Mona (97.00)
Top 3:
1) Mona - 97.00
2) Nada - 90.00
3) Omar - 85.00
```

**ليه الـAverage = 88؟** `(80 + 97 + 85 + 90) / 4 = 88`.

> [!note] تحسين عملي
> استخدمنا `%49s` عشان نحترم حجم الـBuffer؛ ده بيدعم أسماء من غير Spaces فقط. في مشروع حقيقي للأسماء المركبة، استخدم `fgets` مع معالجة الـNewline وParsing مناسب.

### Task 2 — Complex Numbers

**المطلوب:** `struct Complex` فيها `real`, `imaginary`، واكتب **Addition** و**Multiplication** لرقمين Complex.

#### القوانين

لو عندك:

$$
 z_1=a+bi,\quad z_2=c+di
$$

**Addition:**

$$
 z_1+z_2=(a+c)+(b+d)i
$$

**Multiplication:** لأن \(i^2=-1\):

$$
 z_1z_2=(ac-bd)+(ad+bc)i
$$

#### Complete C Solution

```c
#include <stdio.h>

typedef struct {
    double real;
    double imag;
} Complex;

Complex addComplex(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

Complex multiplyComplex(Complex a, Complex b) {
    return (Complex){
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}

void printComplex(Complex x) {
    printf("%.2f %c %.2fi\n",
           x.real, x.imag < 0 ? '-' : '+',
           x.imag < 0 ? -x.imag : x.imag);
}

int main(void) {
    Complex x, y;
    printf("First (real imag): ");
    if (scanf("%lf %lf", &x.real, &x.imag) != 2) return 1;

    printf("Second (real imag): ");
    if (scanf("%lf %lf", &y.real, &y.imag) != 2) return 1;

    printf("Sum = ");
    printComplex(addComplex(x, y));

    printf("Product = ");
    printComplex(multiplyComplex(x, y));
    return 0;
}
```

**Example:** `(2 + 3i)` و`(4 + 5i)`:

- المجموع: `(6 + 8i)`.
- الضرب: `(2×4 - 3×5) + (2×5 + 3×4)i = -7 + 22i`.

> [!tip] Revision Link
> التمرين ده بيجمع بين **Structs + Functions + Return by Value** اللي اتكلمنا عنهم في Slides 156–160.

### Task 3 — Library Management System

**المطلوب حرفيًا من Slide 181:**

- `struct Book` فيها `title`, `author`, `price`, `category`, `availability`.
- `enum BookStatus` و`enum BookCategory`.
- إضافة كتاب، البحث بالعنوان أو المؤلف، تغيير الحالة (**Issue / Return**)، وعدّ الكتب في كل Category.

#### Recommended Data Model

```c
#include <stddef.h>

typedef enum {
    BOOK_AVAILABLE,
    BOOK_ISSUED
} BookStatus;

typedef enum {
    CAT_PROGRAMMING,
    CAT_SCIENCE,
    CAT_LITERATURE,
    CAT_COUNT
} BookCategory;

typedef struct {
    char title[80];
    char author[80];
    double price;
    BookCategory category;
    BookStatus status;
} Book;

#define MAX_BOOKS 100

typedef struct {
    Book books[MAX_BOOKS];
    size_t count;
} Library;
```

**ليه `CAT_COUNT`؟** عشان تقدر تستخدمه لحجم Array عدّاد:

```c
void countByCategory(const Library *lib, size_t counts[CAT_COUNT]) {
    for (int c = 0; c < CAT_COUNT; c++) counts[c] = 0;

    for (size_t i = 0; i < lib->count; i++) {
        BookCategory cat = lib->books[i].category;
        if ((unsigned)cat < (unsigned)CAT_COUNT) counts[cat]++;
    }
}
```

**Search by title or author:** استخدم `strcmp` / `strstr` من `<string.h>`، وحدد هل المقارنة Exact ولا Partial وهل Case-Sensitive.

**Change status:** قبل Issue تأكد إن الكتاب `BOOK_AVAILABLE`؛ وقبل Return تأكد إنه `BOOK_ISSUED`. اعمل Function ترجع Success/Failure.

```c
int issueBook(Book *b) {
    if (b->status != BOOK_AVAILABLE) return 0;
    b->status = BOOK_ISSUED;
    return 1;
}

int returnBook(Book *b) {
    if (b->status != BOOK_ISSUED) return 0;
    b->status = BOOK_AVAILABLE;
    return 1;
}
```

**Menu Design المقترح:**

```text
1. Add book
2. Search by title
3. Search by author
4. Issue book
5. Return book
6. Count books per category
7. Exit
```

> [!warning] Code scope
> السلايد بتحدد مواصفات المشروع، مش بتعرض Solution كامل. اللي فوق **تصميم وحل توضيحي** للتدرّب؛ لسه محتاج تكتب الـInput Loop وFunctions الإضافة والبحث والطباعة للتطبيق الكامل.

### Task 4 — Employee Management System

**المطلوب من Slide 181:**

- بيانات موظف: `id`, `name`, `department`, `type`, `salary/hourly`.
- `enum EmployeeType { FULL_TIME, PART_TIME, INTERN }`.
- `union Compensation` لحفظ **Hourly Rate أو Monthly Salary** حسب نوع الموظف.
- Add/Remove، Filter حسب Department أو Type، حساب Payroll، Search by ID.

#### Recommended Data Model

```c
typedef enum {
    FULL_TIME,
    PART_TIME,
    INTERN
} EmployeeType;

typedef enum {
    DEPT_ENGINEERING,
    DEPT_HR,
    DEPT_FINANCE
} Department;

typedef union {
    double hourly_rate;
    double monthly_salary;
} Compensation;

typedef struct {
    unsigned id;
    char name[60];
    Department department;
    EmployeeType type;
    Compensation compensation;
    double hours_worked;      // Relevant for hourly workers
} Employee;
```

**ليه Union هنا؟** لأن الموظف ممكن تكون بيانات الدفع المرتبطة بيه **راتب شهري أو أجر بالساعة**، ومش محتاج تخزن الاتنين كقيمتين مستقلتين دايمًا.

#### Payroll Rule لازم تحدده قبل الكود

السلايد **مش بتحدد** طريقة حساب مرتب الـ`INTERN` أو الفترة المحاسبية (شهر/أسبوع). مثال لتصميم افتراضي:

- `FULL_TIME` → `monthly_salary`.
- `PART_TIME` → `hourly_rate * hours_worked`.
- `INTERN` → نعتبره Hourly **في المثال فقط**؛ ممكن تختار Stipend حسب المطلوب.

```c
double employeePay(const Employee *e) {
    switch (e->type) {
        case FULL_TIME:
            return e->compensation.monthly_salary;
        case PART_TIME:
        case INTERN:
            return e->compensation.hourly_rate * e->hours_worked;
        default:
            return 0.0;
    }
}
```

**حساب Total Payroll:**

```c
double totalPayroll(const Employee employees[], int n) {
    double total = 0.0;
    for (int i = 0; i < n; ++i) {
        total += employeePay(&employees[i]);
    }
    return total;
}
```

**وظائف لسه مطلوب تنفذها في مشروعك:**

| Function | Expected responsibility |
|---|---|
| `addEmployee` | إضافة مع التحقق من الـCapacity وUnique ID |
| `removeEmployee` | البحث عن ID ثم حذف العنصر وتحريك عناصر Array |
| `findEmployeeById` | ترجع Index أو Pointer للموظف لو موجود |
| `filterByDepartment` | طباعة الموظفين في Department محددة |
| `filterByType` | طباعة الموظفين حسب `EmployeeType` |
| `totalPayroll` | تجميع قيمة الدفع لكل موظف |

> [!tip] Key Lab Connection
> مشروع Library بيربط **Struct + Enum + Arrays + Functions**.
>
> مشروع Employee بيضيف عليهم **Union + Tagged Variant**، وده بالضبط الهدف من آخر جزء في المحاضرة.

---

## Part 13 — Quick Revision and Practice

### Struct vs Union vs Enum vs Bit-Field

| Feature | `struct` | `union` | `enum` | Bit-Field |
|---|---|---|---|---|
| Purpose | تجميع Members مختلفة | بدائل تشارك Storage واحدة | أسماء لحالات/ثوابت صحيحة | عرض محدد بالـBits لعضو Struct/Union |
| Memory | تخزين أعضاء مستقلة + Padding محتمل | مساحة كافية لأكبر عضو + Alignment | نوع عددي بحجم يعتمد على الـCompiler | Bit Storage Layout يعتمد على الـCompiler |
| Access | `obj.member` | `obj.member` | `STATE_IDLE` | `obj.flag` |
| Good for | Sensor/Data Records | Event Payload/Variant | States/Status | Flags/Fields عند التحكم بالـCompiler/Target |
| Main pitfall | Padding / Pointer Copies | قراءة عضو غير المناسب | قيم غير معروفة أو حجم غير ثابت | Bit Order / Portability |

### Important Equations and Rules

```c
ptr->member == (*ptr).member
sizeof(struct_type) >= sum_of_member_sizes  // Padding possible
sizeof(union_type) >= sizeof(largest_member) // Alignment possible
```

```text
Struct by value  -> copies object
Struct by pointer -> copies an address, may modify original
Return struct    -> valid and safe
Return &local    -> invalid/dangling pointer
Self by value    -> invalid
Self by pointer  -> valid
```

### Biggest Mistakes to Avoid

1. اعتقاد إن `struct Book { ... };` لوحده أنشأ Book Object.
2. نسيان الفرق بين `.` و`->`، وكتابة `*ptr.member` بدل `(*ptr).member`.
3. افتراض إن `sizeof(struct)` = مجموع أحجام الأعضاء دايمًا.
4. استخدام Packed Struct كـHardware Register من غير معرفة الـABI والـDatasheet.
5. استخدام `malloc` من غير فحص `NULL` أو نسيان `free`.
6. إرجاع `&localStruct` من Function.
7. افتكار إن Function بتستقبل `struct` بالقيمة هتعدّل الأصل.
8. افتكار إن الـBit-Field المعرّفة بـ4 Bits معناها إن `sizeof` = 0.5 Byte.
9. استخدام Union Member غير مطابق لنوع القيمة الحالية من غير Tag واضح.
10. اعتقاد إن `enum` لازم تكون `int` حجمه 4 Bytes على كل MCU.

### Check Your Understanding

> [!question] Q1
> إيه الفرق بين `struct Person p;` و`struct Person *p;` من حيث التخزين والوصول للأعضاء؟

> [!question] Q2
> ليه الكود ده Invalid؟
>
> ```c
> struct Node { int x; struct Node next; };
> ```

> [!question] Q3
> على Target فيه `char=1`, `uint16_t=2`, `uint32_t=4` وAlignment مساوية للأحجام دي، احسب `sizeof` للكود:
>
> ```c
> struct Test { char a; uint32_t b; char c; };
> ```

> [!question] Q4
> فرّق بين `p.age`, `ptr->age`, `(*ptr).age`.

> [!question] Q5
> إيه الـOutput هنا؟
>
> ```c
> struct X { int a; };
> void edit(struct X x) { x.a = 99; }
> int main(void) { struct X x = {5}; edit(x); printf("%d", x.a); }
> ```
>
> *افترض `#include <stdio.h>`.*

> [!question] Q6
> ليه `struct Book getBook(void)` آمنة كـReturn، لكن `struct Book *getBook(void)` اللي بترجع عنوان Local Object غلط؟

> [!question] Q7
> `unsigned int mode : 3` يقبل كام قيمة مختلفة؟ وإيه أكبر قيمة؟

> [!question] Q8
> ليه الأفضل تستخدم `enum` كـTag مع `union`؟

> [!question] Q9
> اشرح الفرق بين `d.value.i` و`d.i` في حالة Union Named مقابل Anonymous.

> [!question] Q10
> في Employee Management، لو `type = PART_TIME`، أي Member في `Compensation` المفروض تقراه؟ وليه لازم تحدد Rule للحساب؟

### Answers

1. `p` كائن Struct كامل، أما `p` في الصيغة الثانية فهو Pointer محتاج يشاور على Object صالح قبل استخدام `->`.
2. لأن الـNode هتحتوي Node تانية بالقيمة بلا نهاية؛ حجمها غير قابل للتحديد. استخدم `struct Node *next`.
3. غالبًا `12 Bytes`: `a` عند 0، 3 Padding، `b` عند 4–7، `c` عند 8، و3 Tail Padding.
4. `p.age` لعضو كائن، و`ptr->age` لعضو عبر Pointer، و`(*ptr).age` مساوية للأخيرة.
5. `5`، لأن `edit` استقبلت نسخة.
6. إرجاع الـStruct **بالقيمة** صحيح؛ عنوان Local Object بيصبح Dangling عند خروج الدالة.
7. `2^3 = 8` قيم، من `0` لـ`7`.
8. عشان تعرف أي عضو من Union هو المقصود وتختار طريقة القراءة المناسبة.
9. الأولى من خلال Named Member اسمه `value`، والثانية وصول مباشر لأعضاء Anonymous Union.
10. `hourly_rate` على افتراض تصميمنا؛ لأن المطلوب الأصلي مبيحددش قواعد حساب Payroll بالكامل، ولازم تختار تفسير ثابت للأنواع والساعات.

### Mini Cheat Sheet for Obsidian

```c
// STRUCT
struct Point { int x, y; };
struct Point p = {10, 20};

// POINTER TO STRUCT
struct Point *q = &p;
q->x = 30;

// TYPEDEF
typedef struct Point Point;
Point p2 = {1, 2};

// UNION
union Value { int i; float f; };
union Value v = {.i = 42};

// ENUM
enum Mode { OFF, ON, SLEEP };
enum Mode m = ON;

// BIT-FIELD
struct Flags { unsigned ready:1, error:1, mode:2; };

// SELF-REFERENTIAL STRUCT
struct Node { int data; struct Node *next; };
```

> [!success] Final Takeaway
> - **Struct:** كيان واحد بخصائص مختلفة ومستقلة.
> - **Pointer to Struct:** الوصول والتعديل بدون نسخ كل الكائن.
> - **Padding / Alignment:** الحجم الفعلي مش بالضرورة مجموع أحجام الأعضاء.
> - **Bit-Fields:** تمثّل Fields صغيرة بالـBits لكن Layout مش Portable.
> - **Union:** أكتر من شكل للبيانات على نفس مساحة التخزين.
> - **Enum:** تسميات واضحة للحالات والقيم العددية.
> - **Tagged Union:** اجمع `enum + union + struct` لتمثيل Variant بشكل منظّم.
>
> **القاعدة اللي هتحتاجها في الـEmbedded:** لازم تفهم **Memory Representation، Lifetime، Pointer Safety، Compiler / Target Differences** قبل ما تتعامل مع Register Layout أو Dynamic Data Structures.

---

**Source:** `01.EmbeddedC_Final.pdf` — Pages/Slides **140–181**, including **Lab 5** on page 181. الأمثلة الإضافية، تحسينات السلامة، والتصحيحات التوضيحية مميّزة في الشرح مقارنة بنص السلايد.







