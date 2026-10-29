
---

> [!abstract] Overview
> الجزء ده بيربط بين الـ **Arrays** والـ **Pointers**، وبعد كده بيشرح إزاي نفهم الـ **Complex Declarations** في لغة C.
>
> أهم فكرتين لازم تطلع بيهم:
> - تقدر توصل لعناصر الـArray باستخدام `Pointer Arithmetic`.
> - تقدر تفك أي Declaration معقدة لما تبدأ من اسم المتغير وتراعي ترتيب `()`, `[]`, و`*`.

## Study Map

- [[#Array and Pointer Relationship|Array and Pointer Relationship]]
- [[#Accessing a 1D Array with Pointers|Accessing a 1D Array with Pointers]]
- [[#Finding the Size of a 1D Array|Finding the Size of a 1D Array]]
- [[#Accessing a 2D Array with Pointers|Accessing a 2D Array with Pointers]]
- [[#Pointer to an Array|Pointer to an Array]]
- [[#2D Array Example and Memory Representation|2D Array Example and Memory Representation]]
- [[#Counting Array Elements Using Pointer Arithmetic|Counting Array Elements Using Pointer Arithmetic]]
- [[#Complex Declarations and the Spiral Rule|Complex Declarations and the Spiral Rule]]
- [[#Complex Declaration Examples|Complex Declaration Examples]]
- [[#Basic Declarations and Important Differences|Basic Declarations and Important Differences]]
- [[#Quick Revision|Quick Revision]]

---

## Array and Pointer Relationship

في لغة C، فيه علاقة قوية بين الـ`Array` والـ`Pointer`، وده بيسمحلك تتعامل مع العناصر بطريقتين:

- **Array Indexing:** باستخدام `arr[index]`.
- **Pointer Arithmetic:** باستخدام `*(arr + index)`.

> [!important] Array vs Pointer
> اسم الـArray زي `arr` **مش Pointer Variable في حد ذاته**.
>
> لكن في معظم الـExpressions، اسم الـArray بيحصل له `Array-to-Pointer Decay`، يعني بيتحوّل لـPointer بيشاور على أول عنصر.
>
> علشان كده تقدر تستخدم `arr + 1` و`*(arr + 1)`.

## Accessing a 1D Array with Pointers

### 1D Array Access Equation

القانون الأساسي هو:

```c
arr[y] == *(arr + y)
```

معنى كل جزء:

| Expression | المعنى |
|---|---|
| `arr` | في التعبير ده، بيشير لأول عنصر |
| `y` | رقم العنصر أو الـIndex المطلوب |
| `arr + y` | عنوان العنصر رقم `y` |
| `*(arr + y)` | القيمة الموجودة في العنصر رقم `y` |

### Example

```c
#include <stdio.h>

int main(void)
{
    int arr[5] = {10, 20, 30, 40, 50};

    printf("%d\n", arr[2]);
    printf("%d\n", *(arr + 2));

    return 0;
}
```

**Output:**

```text
30
30
```

**شرح المثال:**

1. الـ`arr` فيها خمس عناصر.
2. الـIndex بيبدأ من `0`، فالعنصر `arr[2]` قيمته `30`.
3. `arr + 2` بيحرّك العنوان للعنصر التالت.
4. الـ`*` بتعمل `Dereference` علشان تجيب القيمة الموجودة هناك.

> [!tip] Pointer Arithmetic
> لما تكتب `arr + 2`، العنوان مش بيتحرك بمقدار `2 bytes` بالضرورة.
>
> بيتحرك بمقدار `2 * sizeof(arr[0])`، لأن الحركة بتعتمد على نوع العنصر.

---

## Finding the Size of a 1D Array

### Calculate Number of Elements

تقدر تحسب عدد عناصر الـArray باستخدام:

```c
ArraySize = sizeof(arr) / sizeof(arr[0]);
```

- `sizeof(arr)` بيرجع الحجم الكلي للـArray بالـBytes.
- `sizeof(arr[0])` بيرجع حجم عنصر واحد بالـBytes.
- القسمة بينهم بتديك **عدد العناصر**.

### Example

```c
#include <stdio.h>

int main(void)
{
    int arr[5] = {10, 20, 30, 40, 50};

    size_t count = sizeof(arr) / sizeof(arr[0]);

    printf("Number of elements = %zu\n", count);

    return 0;
}
```

**Output:**

```text
Number of elements = 5
```

**مثال للحساب:** لو الـ`int` حجمه `4 bytes` على الجهاز:

```text
Total array size = 5 * 4 = 20 bytes
One element size = 4 bytes

Number of elements = 20 / 4 = 5
```

> [!warning] Important Condition
> القانون ده لازم تستخدمه في مكان تكون فيه الـArray **لسه Array فعلًا**، زي نفس الـScope اللي متعرّفة فيه.
>
> لما تبعت الـArray لدالة بالشكل `int arr[]`، الـParameter بيتعامل كـPointer، وساعتها `sizeof(arr)` مش هيديك حجم الـArray الأصلية.

### Why It Doesn't Work Inside a Function Parameter

```c
void printCount(int arr[])
{
    // Here arr is treated as int *
    // sizeof(arr) gives pointer size, not full array size.
}
```

الحل المعتاد إنك تبعت **عدد العناصر** للدالة كـParameter منفصل.

---

## Accessing a 2D Array with Pointers

الـ`2D Array` بتتكوّن من Rows وColumns، وتقدر توصل لأي عنصر فيها باستخدام الـIndexing أو الـPointers.

### 2D Array Access — First Form

```c
arr[row][col] == *(arr[row] + col)
```

**خطوات الفهم:**

1. `arr[row]` بيوصلك للـRow المطلوبة.
2. لما الـRow تُستخدم في التعبير ده، بتتحول لـPointer لأول عنصر فيها.
3. `arr[row] + col` بينقلك للـColumn المطلوبة.
4. `*(...)` بترجع **قيمة العنصر**.

### 2D Array Access — Full Pointer Form

```c
arr[row][col] == *(*(arr + row) + col)
```

نفك المعادلة دي جزء جزء:

| Expression | بيعمل إيه؟ |
|---|---|
| `arr` | في التعبير ده، بيشير لأول Row |
| `arr + row` | ينتقل للـRow المطلوبة |
| `*(arr + row)` | يحدد الـRow، والنتيجة تتحول لعنوان أول عنصر فيها |
| `*(arr + row) + col` | ينتقل للـColumn المطلوبة |
| `*(*(arr + row) + col)` | يقرأ قيمة العنصر |

> [!important] احفظ الفرق
> `*(arr + row)` بيوصلك للـRow.
>
> لكن `*(*(arr + row) + col)` بيوصلك **لقيمة عنصر محدد** جوه الـRow.

### Example

```c
int arr[2][3] = {
    {10, 20, 30},
    {40, 50, 60}
};

int value1 = arr[1][2];
int value2 = *(arr[1] + 2);
int value3 = *(*(arr + 1) + 2);
```

الـ3 Variables قيمتهم `60`، لأن المطلوب هو الـRow رقم `1` والـColumn رقم `2`.

---

## Pointer to an Array

### Pointer to a Row in a 2D Array

لو عندنا:

```c
int numbers[3][3];

int (*ptr)[3] = numbers;
```

يبقى:

- الـ`numbers` نوعها `int[3][3]`: عبارة عن `3 Rows` وكل Row فيها `3 ints`.
- الـ`ptr` نوعه `int (*)[3]`: **Pointer to an Array of 3 integers**.
- في التعبير `numbers` بتحصل له عملية `Decay` لـPointer على أول Row.

### How to Read the Declaration

```c
int (*ptr)[3];
```

ابدأ من `ptr`:

1. الأقواس `(*ptr)` معناها إن `ptr` عبارة عن Pointer.
2. الـ`[3]` معناها إنه بيشاور على Array فيها `3 elements`.
3. الـ`int` معناها إن كل عنصر نوعه `int`.

**النتيجة:** `ptr` بيشاور على Array مكوّنة من `3 ints`.

### Accessing Rows

```c
numbers[0]  // First row
numbers[1]  // Second row
numbers[2]  // Third row
```

ومكافئها باستخدام `ptr`:

```c
*(ptr + 0)  // First row
*(ptr + 1)  // Second row
*(ptr + 2)  // Third row
```

علشان توصل لعنصر محدد:

```c
numbers[1][2] == *(*(ptr + 1) + 2)
```

> [!tip] Important Detail
> لما تعمل `ptr + 1`، المؤشر بيتحرك **Row كاملة**، مش عنصر `int` واحد؛ لأن الـPointer نوعه `int (*)[3]`.
>
> يعني الحركة بمقدار `3 * sizeof(int)`.

---

## 2D Array Example and Memory Representation

ده المثال اللي بيوضح الوصول للـ2D Array باستخدام `Pointer to Array`:

```c
#include <stdio.h>

int main(void)
{
    int numbers[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int (*ptr)[3] = numbers;

    printf("%d\n", ptr[0][0]);
    printf("%d\n", ptr[1][2]);
    printf("%d\n", *(*(ptr + 2) + 1));

    return 0;
}
```

**Output:**

```text
1
6
8
```

### Why These Outputs?

**First Expression:**

```c
ptr[0][0]
```

أول Row وأول Column، فالقيمة `1`.

**Second Expression:**

```c
ptr[1][2]
```

تاني Row وتالت Column، فالقيمة `6`.

**Third Expression:**

```c
*(*(ptr + 2) + 1)
```

1. `ptr + 2` → ثالث Row.
2. `*(ptr + 2)` → الوصول للـRow دي.
3. `+ 1` → ثاني Column.
4. الـ`*` الخارجية → قراءة القيمة `8`.

### Memory Representation

الـ2D Array عناصرها مخزنة بشكل متتابع في الذاكرة بنظام `Row-major Order`:

```text
          Col 0   Col 1   Col 2

Row 0       1       2       3
Row 1       4       5       6
Row 2       7       8       9

Memory:
[1][2][3][4][5][6][7][8][9]
```

**أمثلة على الـPointer Access:**

```c
*(*(ptr + 0) + 0)   // 1
*(*(ptr + 0) + 2)   // 3
*(*(ptr + 1) + 1)   // 5
*(*(ptr + 2) + 2)   // 9
```

---

## Counting Array Elements Using Pointer Arithmetic

ممكن تحسب عدد عناصر الـArray من خلال فكرة إن عنوان نهاية الـArray بعد آخر عنصر معروف باستخدام `&arr + 1`.

### The Equation

```c
*(&arr + 1) - arr
```

### Understand Every Part

| Expression | المعنى |
|---|---|
| `arr` | في أغلب التعبيرات يتحول لـPointer لأول عنصر |
| `&arr` | عنوان الـArray كاملة، ونوعه Pointer to Array |
| `&arr + 1` | عنوان بعد نهاية الـArray كاملة |
| `*(&arr + 1)` | في التعبير ده يُستخدم كعنوان بعد آخر عنصر |
| `*(&arr + 1) - arr` | الفرق بوحدة العناصر، أي عدد العناصر |

### Example

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {10, 20, 30, 40, 50};

    size_t count = (size_t)(*(&arr + 1) - arr);

    printf("Number of elements = %zu\n", count);

    return 0;
}
```

**Output:**

```text
Number of elements = 5
```

### Why Does It Work?

الفكرة إن:

- `&arr` نوعه `int (*)[5]`، يعني Pointer على **الـArray كلها**.
- لما نضيف `1`، العنوان بينتقل بمقدار طول الـArray كلها.
- الفرق بين عنوان البداية وعنوان النهاية بيكون `5 elements`.

> [!warning] Prefer sizeof
> الطريقة الأساسية والأوضح في الشغل هي:
>
> `sizeof(arr) / sizeof(arr[0])`
>
> صيغة الـPointer Arithmetic دي موجودة في المحتوى لفهم الفرق بين `arr` و`&arr`. وكمان زي طريقة `sizeof`، مش مناسبة بعد ما الـArray تتحول لـPointer في Function Parameter.
>
> السلايد كاتبة مثال `int arr[] = {};` من غير عناصر. علشان نجرب فعليًا استخدمنا Array متعرّفة بعناصر واضحة.

---

## Complex Declarations and the Spiral Rule

أحيانًا تشوف Declaration فيها أقواس ونجوم وArrays وFunctions مع بعض، فتكون صعبة القراءة.

علشان تفهمها، استخدم طريقة:

**Clockwise / Spiral Rule**

### General Strategy

1. ابدأ من **اسم المتغير أو الدالة**.
2. بص على اللي **يمين الاسم** الأول، مع مراعاة الأقواس.
3. بعد كده بص على **الشمال**.
4. كمّل للخارج تدريجيًا لحد ما توصل لنوع البيانات.

### Operator Precedence in Declarations

| Priority | Operator | المعنى |
|---|---|---|
| أعلى | `()` | Function |
| أعلى | `[]` | Array |
| أقل | `*` | Pointer |
| النهاية | `Data Type` | النوع الأساسي أو نوع الـReturn |

الجدول في المحتوى بيجمع `()` و`[]` في أعلى مستوى، وبعدهم `*`، وفي الآخر نوع البيانات.

> [!important] Parentheses Change Everything
> الفرق بين:
>
> `int *arr[5];`
>
> و:
>
> `int (*ptr)[5];`
>
> هو مكان الأقواس، لكنه بيغير المعنى تمامًا.
>
> الأولى: **Array of Pointers**.
>
> الثانية: **Pointer to Array**.

### A Small Reading Example

```c
int (*func_ptr)(int, float);
```

ابدأ من `func_ptr`:

1. `(*func_ptr)` → Pointer.
2. `(int, float)` → Pointer to a Function بتستقبل `int` و`float`.
3. `int` في البداية → الـFunction بترجع `int`.

**النتيجة:** Pointer to a Function takes `(int, float)` and returns `int`.

---

## Complex Declaration Examples

### Example 1 — Array of Function Pointers

```c
void (*f[10])(int, int);
```

**نفك الـDeclaration:**

1. `f` → اسم المتغير.
2. `f[10]` → Array فيها `10 elements`.
3. `(*f[10])` → كل عنصر Pointer.
4. `(*f[10])(int, int)` → كل Pointer بيشاور على Function بتستقبل `2 ints`.
5. `void` → الـFunction مش بترجع قيمة.

> [!success] Final Meaning
> `f` is an **Array of 10 Pointers to Functions**, each function takes two `int` parameters and returns `void`.

### A Practical Example

```c
#include <stdio.h>

void printSum(int a, int b)
{
    printf("%d\n", a + b);
}

int main(void)
{
    void (*f[10])(int, int) = {printSum};

    f[0](3, 4);

    return 0;
}
```

**Output:**

```text
7
```

هنا `f[0]` شايل عنوان الـFunction اسمها `printSum`، فنقدر نناديها عن طريق الـPointer.

---

### Example 2 — Function Returns Pointer to Array of Function Pointers

```c
char (*(*x())[])();
```

**نفكها واحدة واحدة:**

1. `x` → الاسم.
2. `x()` → `x` عبارة عن Function.
3. `(*x())` → الـFunction بترجع Pointer.
4. `(*x())[]` → الـPointer ده بيشاور على Array حجمها مش محدد هنا.
5. `(*(*x())[])()` → عناصر الـArray عبارة عن Pointers to Functions.
6. `char` → الـFunctions دي بترجع `char`.

> [!important] Final Meaning
> `x` is a **Function returning a Pointer to an Array of Function Pointers**, and these functions return `char`.

**بمعنى أبسط:**

- عندك Function اسمها `x`.
- بتنادي `x` فترجعلك Pointer.
- الـPointer بيشاور على Array.
- الـArray فيها Function Pointers.
- كل Function من دول الـReturn بتاعها `char`.

> [!note] About Empty Parentheses
> في الـC التقليدية، وجود `()` في Function Declaration مش دايمًا معناه تصريح صريح بعدم وجود Parameters، لكنه ممكن يعني إن الـParameter Types مش محددة في التصريح.
>
> لو عايز توضح إن الـFunction مش بتاخد أي Parameters في C قبل C23، بتستخدم `(void)`.

---

### Example 3 — Array of Pointers to Functions Returning Pointer to Array

```c
char (*(*x[3])())[5];
```

**خطوات القراءة:**

1. `x[3]` → Array فيها `3 elements`.
2. `(*x[3])()` → كل عنصر Pointer to Function.
3. `(*(*x[3])())` → كل Function بترجع Pointer.
4. `(*(*x[3])())[5]` → الـPointer بيشاور على Array فيها `5 elements`.
5. `char` → كل عنصر في الـArray الأخيرة نوعه `char`.

> [!success] Final Meaning
> `x` is an **Array of 3 Pointers to Functions**, each function returns a **Pointer to an Array of 5 chars**.

**تخيل التركيب بالشكل ده:**

```text
x
  |
  +-- Array [3]
         |
         +-- Function Pointer
                  |
                  +-- Returns Pointer
                            |
                            +-- Array [5] of char
```

---

### Example 4 — Nested Function Pointers

```c
int *(*(*arr[5])())();
```

**خطوات القراءة:**

1. `arr[5]` → Array فيها `5 elements`.
2. `(*arr[5])()` → كل عنصر Pointer to Function.
3. `(*(*arr[5])())` → الـFunction بترجع Pointer.
4. `(*(*arr[5])())()` → الـPointer الراجع بيشاور على Function تانية.
5. `int *` → الـFunction التانية بترجع Pointer to `int`.

> [!success] Final Meaning
> `arr` is an **Array of 5 Pointers to Functions** that return **Pointers to Functions** that return **Pointers to int**.

```text
arr[5]
   |
   +-- Pointer to Function
                |
                +-- Returns Pointer to Function
                                   |
                                   +-- Returns int *
```

> [!tip] How to Avoid Confusion
> حاول تقرأ من اسم `arr` للخارج، ومتبدأش من `int *` اللي في أول السطر.
>
> ده أهم سبب بيخلي الـSpiral Rule مفيدة في التصريحات المعقدة.

---

### Example 5 — Function Receives and Returns Function Pointers

```c
void (*iti(int std, void (*func)(int)))(int);
```

**ابدأ من `iti`:**

1. `iti(...)` → Function اسمها `iti`.
2. أول Parameter هو `int std`.
3. تاني Parameter هو `void (*func)(int)`.
4. الـParameter التاني Pointer to Function تستقبل `int` وترجع `void`.
5. الـReturn Type بتاع `iti` هو `void (*)(int)`.

> [!success] Final Meaning
> `iti` is a **Function** taking:
> - an `int`,
> - a Function Pointer taking `int` and returning `void`,
>
> and returning **another Function Pointer** taking `int` and returning `void`.

**شكل مبسط للفكرة:**

```text
iti
 ├── Input 1: int
 ├── Input 2: Function Pointer (int -> void)
 └── Return : Function Pointer (int -> void)
```

### Optional: Make It Easier With typedef

المثال ده للتوضيح مش تغيير للـDeclaration الأصلية:

```c
typedef void (*Action)(int);

Action iti(int std, Action func);
```

الـ`typedef` خلّت شكل الـFunction أبسط، مع الحفاظ على نفس المعنى.

---

## Basic Declarations and Important Differences

### Pointer to int

```c
int *ptr;
```

المعنى: `ptr` is a **Pointer to int**.

### Pointer to Pointer to int

```c
int **ptr;
```

المعنى: `ptr` is a **Pointer to a Pointer to int**.

يعني:

```text
ptr --> pointer --> int value
```

### Pointer to Array of 5 ints

```c
int (*ptr)[5];
```

المعنى: `ptr` is a **Pointer to an Array of 5 ints**.

### Array of 5 Pointers to int

```c
int *arr[5];
```

المعنى: `arr` is an **Array of 5 Pointers to int**.

### Very Important Comparison

| Declaration | المعنى |
|---|---|
| `int *ptr;` | Pointer to int |
| `int **ptr;` | Pointer to Pointer to int |
| `int (*ptr)[5];` | Pointer to Array of 5 ints |
| `int *arr[5];` | Array of 5 Pointers to int |

> [!warning] Common Exam Question
> `int (*ptr)[5]` **مش** زي `int *ptr[5]`.
>
> الأقواس بتحدد هل الـPointer هو اللي بيشاور على Array كاملة، ولا الـArray نفسها بتحتوي Pointers.

---

### Function Pointer Taking int and float

```c
int (*func_ptr)(int, float);
```

الـ`func_ptr` عبارة عن Pointer to Function:

- بتستقبل `int`.
- وبتستقبل `float`.
- وبترجع `int`.

### Array of Function Pointers

```c
int (*arr[3])(char *);
```

ابدأ من `arr`:

1. `arr[3]` → Array من `3 elements`.
2. `(*arr[3])` → كل عنصر Pointer.
3. `(char *)` → Pointer to Function تستقبل `char *`.
4. `int` → والـFunction بترجع `int`.

**النتيجة:** Array فيها `3 Function Pointers`، وكل Function بتستقبل `char *` وبترجع `int`.

---

### Complex Function Declaration — signal

```c
char *(*signal(int, void (*)(int)))(int);
```

**تفكيك التصريح:**

1. `signal(...)` → Function اسمها `signal`.
2. أول Parameter → `int`.
3. تاني Parameter → Function Pointer نوعه `void (*)(int)`.
4. الـFunction `signal` بترجع Pointer to Function.
5. الـFunction اللي الـPointer بيشاور عليها بتستقبل `int`.
6. الـFunction دي بترجع `char *`.

> [!success] Final Meaning
> `signal` is a **Function** that takes an `int` and a Function Pointer `(int -> void)`, and returns a Function Pointer `(int -> char *)`.

```text
signal
 ├── Input 1: int
 ├── Input 2: Function Pointer (int -> void)
 └── Return : Function Pointer (int -> char *)
```

> [!note] Important
> ركز إن آخر Return هو `char *`، مش `char`.
>
> النجمة المرتبطة بـ`char` معناها **Pointer to char**.

---

## Quick Revision

### Essential Equations

| Concept | Equation |
|---|---|
| 1D Array Access | `arr[i] == *(arr + i)` |
| 1D Array Element Count | `sizeof(arr) / sizeof(arr[0])` |
| 2D Array Access | `arr[i][j] == *(arr[i] + j)` |
| Full 2D Pointer Form | `arr[i][j] == *(*(arr + i) + j)` |
| Element Count via Pointer Arithmetic | `*(&arr + 1) - arr` |

### Declarations Cheat Sheet

| Syntax | Meaning |
|---|---|
| `int *p;` | Pointer to int |
| `int **p;` | Pointer to Pointer to int |
| `int (*p)[5];` | Pointer to Array of 5 ints |
| `int *p[5];` | Array of 5 Pointers to int |
| `int (*p)(int, float);` | Pointer to Function returning int |
| `int (*p[3])(char *);` | Array of 3 Function Pointers |
| `void (*f[10])(int, int);` | Array of 10 Function Pointers |
| `void (*iti(int, void (*)(int)))(int);` | Function taking and returning Function Pointers |

### Practice Questions

> [!question] Question 1
> إيه الفرق بين `int (*p)[5]` و`int *p[5]`؟

> [!question] Question 2
> لو عندك `int matrix[3][3]`، اكتب `matrix[2][1]` باستخدام Full Pointer Form.

> [!question] Question 3
> إيه المشكلة في استخدام `sizeof(arr) / sizeof(arr[0])` جوه Function بتستقبل `int arr[]`؟

> [!question] Question 4
> اقرأ التصريح ده وفسّر معناه:
>
> `void (*f[10])(int, int);`

> [!question] Question 5
> في التصريح `char *(*signal(int, void (*)(int)))(int);`، إيه نوع الـReturn بتاع `signal`؟

### Answers

1. الأولى Pointer to Array فيها `5 ints`، والتانية Array فيها `5 Pointers to int`.
2. `*(*(matrix + 2) + 1)`.
3. لأن الـArray Parameter بيتعامل كـPointer، والـ`sizeof` بيجيب حجم الـPointer مش الـArray كلها.
4. Array فيها `10 Pointers to Functions`؛ كل Function بتستقبل `2 ints` وبترجع `void`.
5. Pointer to Function بتستقبل `int` وبترجع `char *`.

> [!important] Final Takeaway
> علشان تفهم الـ**Arrays with Pointers** ركز على الفرق بين **Address** و**Value**.
>
> وعلشان تفهم الـ**Complex Declarations** ابدأ دايمًا من **اسم المتغير**، وبعدها اقرأ الـ`[]` والـ`()` والـ`*` حسب الأقواس والأولوية.
