
---


# ‏Embedded C — الدوال والمصفوفات والنصوص والمؤشرات

## ‏خريطة المذاكرة

- [[#‏Functions — الدوال وتنظيم البرنامج|Functions — الدوال]]
- [[#‏Function Arguments — طرق تمرير البيانات|Function Arguments]]
- [[#‏Advanced Functions — الدوال المتقدمة|Advanced Functions]]
- [[#‏Arrays — المصفوفات|Arrays]]
- [[#‏Multidimensional Arrays — المصفوفات متعددة الأبعاد|Multidimensional Arrays]]
- [[#‏Arrays and Functions — تمرير وإرجاع المصفوفات|Arrays and Functions]]
- [[#‏Strings — التعامل مع النصوص|Strings]]
- [[#‏String and Memory Functions — أهم دوال المكتبة|String and Memory Functions]]
- [[#‏Pointers — فهم المؤشرات من الصفر|Pointers]]
- [[#‏Pointer Types — أنواع المؤشرات وأخطاء التعامل معاها|Pointer Types]]
- [[#‏Pointer Arithmetic — الحساب بالمؤشرات|Pointer Arithmetic]]
- [[#‏Dynamic Memory Allocation — حجز الذاكرة وقت التشغيل|Dynamic Memory Allocation]]
- [[#‏Advanced Pointer Applications — استخدامات متقدمة|Advanced Pointer Applications]]
- [[#‏Revision and Practice — مراجعة وتدريبات|Revision and Practice]]

---

# ‏Functions — الدوال وتنظيم البرنامج

## ‏يعني إيه Function؟

‏الـ **Function** هي جزء مستقل من الكود مسؤول عن تنفيذ مهمة محددة، وممكن نناديه أكتر من مرة بدل ما نكرر نفس الأوامر.

‏تخيّل برنامج بيقرأ درجة الحرارة، يحوّل الوحدة، يقارنها بحد أمان، وبعدها يعرض النتيجة. بدل ما تكتب كل ده جوّه `main()`، تقدر تقسّمه إلى دوال، كل واحدة مسؤولة عن خطوة.

‏ده اسمه **Modular Programming**: تقسيم البرنامج إلى أجزاء صغيرة يسهل فهمها، اختبارها، إعادة استخدامها، وصيانتها.

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main(void) {
    int result = add(10, 20);
    printf("Result = %d\n", result);
    return 0;
}
```

‏النتيجة: `Result = 30`.

### ‏ليه بنستخدم Functions؟

- ‏**Reusability:** ‏تستخدم نفس الوظيفة في أكتر من مكان.
- ‏**Readability:** ‏كل جزء ليه اسم ومعنى واضح.
- ‏**Maintainability:** ‏تصلّح المشكلة في وظيفة واحدة بدل أماكن كثيرة.
- ‏**Debugging & Testing:** ‏تختبر كل وظيفة لوحدها.
- ‏**Top-down design:** ‏تبدأ من المهمة الكبيرة، وتقسمها إلى مهام أصغر.

## ‏Declaration vs Definition vs Call

‏في تلات مصطلحات لازم تفرق بينهم:

| المصطلح | المعنى | المثال |
|---|---|---|
| ‏**Declaration / Prototype** | ‏بتعرّف الـ Compiler إن الدالة موجودة، ونوع الناتج والـ Parameters بتوعها | `int add(int, int);` |
| ‏**Definition** | ‏التنفيذ الفعلي: جسم الدالة والتعليمات | `int add(int a,int b) { return a+b; }` |
| ‏**Call** | ‏استدعاء الدالة لتنفيذ مهمتها | `add(3, 4)` |

```c
#include <stdio.h>

int multiply(int x, int y);   // Declaration

int main(void) {
    int answer = multiply(3, 4);  // Call
    printf("%d\n", answer);
    return 0;
}

int multiply(int x, int y) {   // Definition
    return x * y;
}
```

‏ليه الـ **Prototype** مهم؟ لو هتستخدم الدالة قبل تعريفها، الـ Compiler لازم يعرف شكلها مسبقًا. ونفس الفكرة مهمة لما الدالة تكون متعرفة في ملف C تاني.

## ‏أجزاء الـ Function

```c
float calculate_average(int sum, int count) {
    return (float)sum / count;
}
```

| الجزء | المعنى |
|---|---|
| `float` | ‏**Return Type** — نوع القيمة اللي الدالة بترجعها |
| `calculate_average` | ‏**Function Name** — اسم الدالة |
| `(int sum, int count)` | ‏**Parameters** — البيانات اللي الدالة بتستقبلها |
| `{ ... }` | ‏**Function Body** — التعليمات اللي بتنفذها |
| `return` | ‏ترجع قيمة للدالة اللي نادت عليها، وتنهي التنفيذ الحالي |

> [!important] ‏`void`
> ‏لو الدالة **مش بترجع قيمة**، استخدم `void` كـ Return Type. ولو **مش بتستقبل Parameters**، اكتب `(void)` للتوضيح في لغة C.

```c
#include <stdio.h>

void show_welcome(void) {
    printf("Welcome!\n");
}

int main(void) {
    show_welcome();
    return 0;
}
```

## ‏الدالة `main()`

‏دي نقطة البداية المعتادة لتنفيذ برنامج C. منها نقدر ننادي بقية الدوال، وبعد انتهائها نرجع نكمّل في `main()`.

‏من الصور الشائعة لتعريفها:

```c
int main(void) {
    return 0;
}
```

```c
int main(int argc, char *argv[]) {
    return 0;
}
```

‏غالبًا `return 0` معناها **نجاح التنفيذ**، والقيمة غير الصفرية معناها **إن فيه حالة خطأ**.

### ‏Command-line Arguments

- ‏`argc` اختصار **Argument Count**، وبيحتوي عدد الوسائط اللي اتبعتت للبرنامج.
- ‏`argv` اختصار **Argument Vector**، وهي مصفوفة من النصوص اللي تمثل الوسائط.
- ‏`argv[0]` بيمثل اسم/مسار تشغيل البرنامج حسب بيئة التشغيل.
- ‏`argv[1]` أول وسيط إضافي، و`argv[argc]` بيساوي `NULL`.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Arguments count: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
```

> [!warning] ‏ملحوظة في Embedded Systems
> ‏في بيئات **Bare-metal** تنفيذ البرنامج ممكن يبدأ فعليًا من **Startup Code / Reset Handler** قبل الوصول لـ `main()`، وده لا يغيّر إن `main()` هي نقطة الدخول الأساسية لكود التطبيق المكتوب بـ C.

---

# ‏Function Arguments — طرق تمرير البيانات

## ‏Actual vs Formal Parameters

‏خلينا نبص على الاستدعاء ده:

```c
int add(int x, int y) {
    return x + y;
}

int main(void) {
    int a = 10;
    int b = 20;
    int c = add(a, b);
    return 0;
}
```

- ‏`a` و`b`: دول الـ **Actual Arguments** — القيم/المتغيرات اللي بعتها وقت الاستدعاء.
- ‏`x` و`y`: دول الـ **Formal Parameters** — المتغيرات اللي الدالة بتستقبل فيها البيانات.
- ‏`c`: بيستقبل الـ **Return Value**، وهنا بيساوي `30`.

## ‏Call by Value — تمرير نسخة من القيمة

‏دي الطريقة الافتراضية في C: الدالة بتاخد **نسخة** من قيمة المتغير؛ لذلك تعديل النسخة مش بيغيّر الأصل.

```c
#include <stdio.h>

void change(int x) {
    x = 99;
}

int main(void) {
    int a = 10;
    change(a);
    printf("a = %d\n", a);  // a = 10
    return 0;
}
```

‏**ليه الناتج 10؟** لأن `x` متغير محلي جوّه `change()`، ومش هو نفس مكان `a` في الذاكرة.

### ‏قصة الذاكرة في `add()`

‏لو استدعينا `add(10, 20)`:

1. ‏القيمة `10` بتتنسخ داخل `x`، والقيمة `20` داخل `y`.
2. ‏الدالة بتحسب `z = x + y`، يعني الناتج `30`.
3. ‏بتنفّذ `return z` وترجّع الناتج للـ Caller.
4. ‏المتغيرات المحلية العادية جوّه الدالة عمرها بينتهي بخروج الدالة.

> [!tip] ‏احفظ القاعدة
> ‏**Call by Value = نسخة من البيانات → الأصل مش بيتغيّر مباشرةً.**

## ‏Call by Address — تمرير عنوان المتغير

‏لو عايز الدالة تعدّل المتغير الأصلي، هتبعت **عنوانه** باستخدام `&`، وتستقبل العنوان داخل **Pointer**.

```c
#include <stdio.h>

void change(int *p) {
    *p = 99;
}

int main(void) {
    int a = 10;
    change(&a);
    printf("a = %d\n", a);  // a = 99
    return 0;
}
```

‏اتتبع الحكاية:

1. ‏`&a` معناها: هات **عنوان** المتغير `a`.
2. ‏`int *p` معناها: `p` مؤشر لمتغير نوعه `int`.
3. ‏الـ Pointer بياخد عنوان `a`.
4. ‏`*p = 99` معناها: غيّر القيمة الموجودة **في العنوان ده**.
5. ‏بالتالي قيمة `a` نفسها بتتغير لـ `99`.

‏الفرق بين الرمزين هنا مهم جدًا:

| التعبير | معناها |
|---|---|
| `a` | ‏قيمة المتغير |
| `&a` | ‏عنوان المتغير في الذاكرة |
| `p` | ‏العنوان المخزّن جوّه الـ Pointer |
| `*p` | ‏القيمة الموجودة في العنوان اللي `p` بيشاور عليه |

> [!important] ‏دقة مهمة في C
> ‏المحاضرة بتسمي الطريقة دي **Call by Reference (with pointers)**. تقنيًا لغة C نفسها بتمرّر **كل الـ Arguments بالقيمة**؛ في الحالة دي القيمة المنسوخة هي **العنوان**. فالأدق تقول **Passing a Pointer by Value** أو **Call by Address**.

### ‏مثال عملي — Swap

```c
#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void) {
    int a = 5, b = 9;
    swap(&a, &b);
    printf("a=%d, b=%d\n", a, b); // a=9, b=5
    return 0;
}
```

‏من غير الـ Pointers، لو غيرت نسخ القيم داخل `swap`، المتغيرين الأصليين مش هيتبدّلوا.

---

# ‏Advanced Functions — الدوال المتقدمة

## ‏Variadic Functions — دالة تستقبل عددًا متغيرًا من الـ Arguments

‏أحيانًا عدد القيم اللي هتدخل الدالة مش ثابت. مثال مشهور: `printf()`، لأنك تقدر تبعت لها أكتر من قيمة مع الـ Format String.

‏الـ **Variadic Function** بتستخدم `...` بعد **على الأقل وسيط ثابت مسمّى**، وبتحتاج `#include <stdarg.h>`.

| الـ Macro | وظيفته |
|---|---|
| `va_list` | ‏النوع اللي بيمثل قائمة الوسائط المتغيرة |
| `va_start(ap, last)` | ‏بدء قراءة الوسائط بعد آخر وسيط ثابت |
| `va_arg(ap, type)` | ‏قراءة الوسيط التالي بالنوع اللي حددته |
| `va_copy(dest, src)` | ‏عمل نسخة من حالة قراءة الوسائط |
| `va_end(ap)` | ‏إنهاء التعامل مع قائمة الوسائط |

```c
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    return total;
}

int main(void) {
    printf("%d\n", sum(4, 10, 20, 30, 40)); // 100
    return 0;
}
```

‏`count` بيقول للدالة تقرأ كام قيمة من الجزء المتغير. من غير معلومة زي دي أو Format String مناسب، الدالة مش هتعرف عدد القيم وأنواعها بشكل آمن.

> [!warning] ‏لازم نوع `va_arg` يطابق نوع الوسيط بعد قواعد ترقية الأنواع
> ‏مثلًا `float` بيتبعت عادةً كـ `double` في `...`، وبعض الأنواع الصحيحة الصغيرة بتترقّى لـ `int`.

## ‏Callback Functions — لما دالة تستقبل دالة تانية

‏الـ **Callback** هي دالة بتتبعت لدالة تانية على هيئة **Function Pointer**؛ والدالة التانية تقدر تناديها وقت ما تحتاج.

‏الفكرة أساسية في **Event Handling**، والتعامل مع الأحداث والمقاطعات والبرمجة غير المتزامنة.

```c
#include <stdio.h>

int square(int x) {
    return x * x;
}

int double_value(int x) {
    return x * 2;
}

void process_numbers(const int arr[], int size,
                     int (*operation)(int)) {
    for (int i = 0; i < size; i++) {
        printf("%d ", operation(arr[i]));
    }
    printf("\n");
}

int main(void) {
    int data[] = {1, 2, 3};
    process_numbers(data, 3, square);       // 1 4 9
    process_numbers(data, 3, double_value); // 2 4 6
    return 0;
}
```

‏`process_numbers()` ثابتة، لكن طريقة المعالجة بتتغير حسب الدالة اللي بعتهالها. وده بيخلّي الكود **مرن وقابل لإعادة الاستخدام**.

## ‏Recursive Functions — دالة بتنادي نفسها

‏الـ **Recursion** معناها إن الدالة بتستدعي نفسها لحل مشكلة ممكن تتقسم لنسخ أصغر من نفس المشكلة.

‏لازم يكون عندنا:

- ‏**Base Case:** ‏حالة توقف الاستدعاءات.
- ‏**Recursive Case:** ‏الدالة تنادي نفسها بمشكلة أصغر.

```c
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;       // Base case
    }
    return n * factorial(n - 1);
}

int main(void) {
    printf("%d\n", factorial(5)); // 120
    return 0;
}
```

‏الخطوات المفهومية:

```text
factorial(5)
= 5 * factorial(4)
= 5 * 4 * factorial(3)
= 5 * 4 * 3 * factorial(2)
= 5 * 4 * 3 * 2 * factorial(1)
= 5 * 4 * 3 * 2 * 1
= 120
```

> [!warning] ‏Recursion في Embedded C
> ‏كل استدعاء ممكن يستهلك مساحة إضافية على الـ **Stack**. لو مفيش Base Case أو التعمق كبير، ممكن يحصل **Stack Overflow**، ودي مشكلة مهمة جدًا في الأنظمة محدودة الـ RAM.

---

# ‏Arrays — المصفوفات

## ‏فكرة الـ Array

‏الـ **Array** هي مجموعة عناصر من **نفس النوع** وموجودة جنب بعض في أماكن متجاورة من الذاكرة (**Contiguous Memory**). بنوصل لكل عنصر برقم اسمه **Index**.

```c
int arr[5] = {2, 4, 8, 12, 16};
```

‏ممكن تتخيل محتواها كده:

| الـ Index | `0` | `1` | `2` | `3` | `4` |
|---|---:|---:|---:|---:|---:|
| ‏القيمة | 2 | 4 | 8 | 12 | 16 |

‏مهم:

- ‏أول عنصر `arr[0]`، وآخر عنصر `arr[4]` في المثال.
- ‏عدد عناصر المصفوفة هنا `5`، لكن آخر Index هو `4`.
- ‏حجم المصفوفة العادية ثابت طول عمرها.
- ‏التخزين المتجاور بيخلّي الوصول لأي عنصر بالـ Index سريع.

```c
#include <stdio.h>

int main(void) {
    int arr[5] = {2, 4, 8, 12, 16};

    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}
```

### ‏Declaration وInitialization

```c
int a[5];                       // Declare 5 elements
int b[5] = {1, 2, 3, 4, 5};     // Full initialization
int c[5] = {1, 2};              // Remaining elements become zero
int d[] = {10, 20, 30};         // Compiler infers size = 3
```

‏لما تحتاج تعرف عدد عناصر **Array حقيقية داخل نفس الـ Scope**، تقدر تستخدم:

```c
int values[] = {10, 20, 30, 40};
size_t count = sizeof(values) / sizeof(values[0]);
```

> [!warning] ‏Out of Bounds
> ‏الكتابة أو القراءة خارج حدود المصفوفة زي `arr[5]` لمصفوفة فيها خمس عناصر سلوك غير معرّف (**Undefined Behavior**)؛ مش مجرد قيمة غلط، وممكن يعمل Crash أو يبوّظ بيانات تانية في الذاكرة.

---

# ‏Multidimensional Arrays — المصفوفات متعددة الأبعاد

## ‏2D Array — صفوف وأعمدة

‏المصفوفة ذات البعدين هي **Array of Arrays**، ومفيدة للجداول والمصفوفات الرياضية.

```c
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

| ‏الصف | ‏العمود الأول | ‏العمود الثاني | ‏العمود الثالث |
|---|---:|---:|---:|
| `0` | 1 | 2 | 3 |
| `1` | 4 | 5 | 6 |

‏مثلًا `matrix[1][2]` بيساوي `6`؛ لأننا في الصف الثاني والعمود الثالث.

```c
#include <stdio.h>

int main(void) {
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
    return 0;
}
```

‏العناصر بتتخزن في الذاكرة بترتيب **Row-major Order**؛ يعني صف كامل وبعده الصف اللي بعده.

## ‏3D Array — صفحات وصفوف وأعمدة

```c
int cube[2][2][3] = {
    {{1, 2, 3}, {4, 5, 6}},
    {{7, 8, 9}, {10, 11, 12}}
};
```

‏اقرأها بالشكل ده:

- ‏البُعد الأول: صفحتين (**2 pages**).
- ‏البُعد الثاني: كل صفحة فيها صفين (**2 rows**).
- ‏البُعد الثالث: كل صف فيه ثلاثة أعمدة (**3 columns**).

‏إجمالي العناصر `2 × 2 × 3 = 12` عنصرًا.

```c
printf("%d\n", cube[1][0][2]);  // 9
```

‏العنصر `9` موجود في الصفحة الثانية، الصف الأول، العمود الثالث.

>[!important] Random Access in Arrays
> الـ **Array** بتدعم خاصية **Random Access**، يعني تقدر توصل لأي عنصر مباشرة باستخدام الـ **Index**، من غير ما تحتاج تعدّي على العناصر اللي قبله.
>
> - **Time Complexity:** `O(1)` — Constant Time.
> - السبب إن عناصر الـ Array متخزنة في أماكن متجاورة في الذاكرة (**Contiguous Memory**).
> - الـ CPU يقدر يحسب عنوان أي عنصر باستخدام الـ Base Address والـ Index.
>
> **Address Formula:**
>
> `Address(arr[i]) = Base Address + (i * sizeof(element))`

```c
int arr[5] = {10, 20, 30, 40, 50};

printf("%d", arr[4]); // Output: 50
```

>[!tip] Important Difference
> **Random Access** معناها الوصول المباشر لأي عنصر في زمن ثابت `O(1)`، لكن **Searching** عن قيمة غير معروفة مكانها ممكن يحتاج `O(n)` في الـ Unsorted Array.

---

# ‏Arrays and Functions — تمرير وإرجاع المصفوفات

## ‏تمرير Array للدالة

‏لما تمرّر مصفوفة عادية لدالة، اسمها غالبًا بيتحوّل تلقائيًا إلى **Pointer لأول عنصر** — العملية دي اسمها **Array-to-pointer Decay**.

```c
#include <stdio.h>

void print_array(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

int main(void) {
    int numbers[] = {10, 20, 30, 40};
    print_array(numbers, 4);
    return 0;
}
```

‏يعني مش بيتم نسخ الأربع عناصر تلقائيًا للدالة؛ اللي بيتبعت هو عنوان أول عنصر. عشان كده غالبًا لازم تمرّر **حجم المصفوفة** بشكل منفصل.

> [!important] ‏`arr[]` و`*arr` في Parameter
> ‏في تعريف Parameter زي `void f(int arr[])`، ده مكافئ تقريبًا لـ `void f(int *arr)`؛ الاتنين بيستقبلوا مؤشر، مش Array كاملة. **لكن Array نفسها مش Pointer**؛ فيه فرق مهم بين النوعين واستخدام `sizeof` عليهم.

## ‏المشي على العناصر باستخدام Pointer

```c
#include <stdio.h>

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int *x = a;

    for (int i = 0; i < 5; i++) {
        printf("%d ", *x);
        x++;
    }
    return 0;
}
```

‏الفكرة:

- ‏في البداية `x == &a[0]`.
- ‏`*x` بتجيب القيمة اللي المؤشر واقف عندها.
- ‏`x++` بتنقل المؤشر **للعنصر التالي**، مش بالضرورة بايت واحد.
- ‏لو `sizeof(int) == 4`، العنوان يزيد 4 بايت في كل خطوة.

## ‏إرجاع Array من Function

‏في C **مش بترجع Array عادية مباشرةً كـ Return Value**، لكن ممكن ترجع Pointer لعناصر عُمرها لسه مستمر بعد خروج الدالة.

‏مثال مطابق للفكرة المعروضة في المحاضرة باستخدام `static`:

```c
#include <stdio.h>

int *get_numbers(void) {
    static int numbers[3] = {10, 20, 30};
    return numbers;
}

int main(void) {
    int *p = get_numbers();
    for (int i = 0; i < 3; i++) {
        printf("%d ", p[i]);
    }
    return 0;
}
```

‏الـ `static` بتخلّي البيانات تفضل موجودة بعد انتهاء استدعاء الدالة. وبدائل تانية هنشوفها لاحقًا: **Dynamic Allocation** أو إن الدالة تكتب في Array بعتها لها من `main()`.

> [!warning] ‏ممنوع ترجع عنوان Array محلية عادية
> ‏لو عرّفت `int arr[3]` جوّه الدالة من غير `static` ورجّعت `arr`، هترجع عنوان بيانات انتهى عمرها بمجرد خروج الدالة.

---
# ‏Strings — التعامل مع النصوص

## ‏الـ String في لغة C

‏لغة C معندهاش **String Data Type** مستقل بالشكل الموجود في لغات تانية؛ الـ String عبارة عن **Array of `char`**، وآخرها حرف خاص اسمه **Null Terminator** ورمزه `\0`.

```c
char name[] = "Ali";
```

‏في الذاكرة الصورة تبقى تقريبًا:

| ‏المكان | `name[0]` | `name[1]` | `name[2]` | `name[3]` |
|---|---|---|---|---|
| ‏القيمة | `'A'` | `'l'` | `'i'` | `'\0'` |

‏الكلمة فيها **3 حروف**، لكن محتاجة **4 بايت** لتخزينها مع `\0`، بافتراض إن `char` بايت واحد (وده تعريف البايت في C، لكن عدد الـ Bits فيه يعتمد على المنصة).

```c
#include <stdio.h>

int main(void) {
    char name[] = "Ali";
    printf("%s\n", name);
    printf("%c\n", name[0]);
    return 0;
}
```

## ‏قراءة النصوص بـ `scanf` ومشكلتها

‏`scanf("%s", name)` بتقرأ كلمة لحد أول **Whitespace** زي مسافة أو Tab أو سطر جديد. وبالتالي لو المستخدم كتب جملة فيها مسافات، مش هتتقرأ كلها.

‏استخدام `scanf` من غير تحديد حجم ممكن يؤدي إلى **Buffer Overflow**. لو هتقرأ كلمة محدودة من Buffer حجمه `20`:

```c
char name[20];
scanf("%19s", name);
```

‏ليه `19`؟ لأن آخر مكان لازم نسيبه لحرف النهاية `\0`.

‏ولو عايز جملة كاملة فيها مسافات، استخدم `fgets`:

```c
#include <stdio.h>

int main(void) {
    char sentence[100];
    printf("Enter a sentence: ");

    if (fgets(sentence, sizeof(sentence), stdin) != NULL) {
        printf("You entered: %s", sentence);
    }
    return 0;
}
```

> [!tip] ‏فرق مهم
> ‏`scanf("%s", ...)` مناسب للكلمات **من غير مسافات** عند تحديد حد أقصى. ‏`fgets()` مناسبة لقراءة **سطر**، لكن غالبًا بتحتفظ بحرف الـ Newline إن اتقرأ.

## ‏Array of Strings — مصفوفة من النصوص

‏عندك أكتر من طريقة. المحاضرة قارنت طريقة المصفوفة الثنائية بمصفوفة المؤشرات.

### ‏Array ثنائية الأبعاد

```c
char words[3][10] = {
    "Geek",
    "Geeks",
    "Geeksfor"
};
```

‏هنا فيه `3` صفوف، وكل صف محجوز له `10` بايت، حتى لو الكلمة الفعلية صغيرة. ده بيخلّي التخزين منتظم لكنه ممكن يترك **مساحات غير مستخدمة**.

### ‏Array of Character Pointers

```c
const char *words[] = {
    "Geek",
    "Geeks",
    "Geeksfor"
};
```

‏هنا كل عنصر في المصفوفة هو **Pointer** لبداية String. وده يتيح كلمات بأطوال مختلفة من غير تحديد مساحة ثابتة كبيرة لكل كلمة. لكن المؤشرات نفسها ليها حجم، والـ String Literals لازم تتعامل معاها على إنها **Read-only**.

| المقارنة | `char words[3][10]` | `const char *words[3]` |
|---|---|---|
| ‏العناصر | ‏مصفوفات حروف ثابتة الطول | ‏مؤشرات لنصوص |
| ‏المحتوى | ‏ممكن تعديل الحروف داخل كل صف | ‏مينفعش تعديل الـ Literals عبر المؤشرات دي |
| ‏المساحة | ‏سعة ثابتة لكل صف | ‏مؤشرات + مكان كل Literal |
| ‏استخدام شائع | ‏لما تحتاج Buffers قابلة للكتابة | ‏لقوائم أسماء ورسائل ثابتة |

---

# ‏String and Memory Functions — أهم دوال المكتبة

‏الدوال الخاصة بالنصوص موجودة غالبًا في `string.h`. **مش معنى وجود مكتبة إنك مش محتاج تهتم بحجم الـ Buffer**؛ لازم دايمًا تعرف عدد البايتات المتاحة.

## ‏Copying — نسخ النصوص

### ‏`strcpy(dest, src)`

‏بتنسخ نص المصدر للوجهة، **بما فيه `\0`**. شرط أساسي: الـ Destination يكون حجمه كافيًا.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char src[] = "Hello";
    char dest[20];

    strcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}
```

### ‏`strncpy(dest, src, n)`

‏بتنسخ بحد أقصى `n` حرفًا، **لكن مش بتضمن وضع `\0`** لو المصدر طوله `n` أو أكتر.

```c
#include <string.h>

char dest[6];
strncpy(dest, "Hello World", sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

> [!warning] ‏خطأ شائع جدًا
> ‏مجرد كتابة `strncpy()` مش معناها إن النسخ آمن تلقائيًا. لازم تحسب الحجم وتضمن إن النص النهائي **Null-terminated** لما هتستخدمه كـ C String.

## ‏Concatenation — دمج النصوص

- ‏`strcat(dest, src)` بتضيف المصدر في نهاية الوجهة.
- ‏`strncat(dest, src, n)` بتضيف بحد أقصى `n` حرفًا من المصدر.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char text[30] = "Hello";
    strcat(text, " World");
    printf("%s\n", text); // Hello World
    return 0;
}
```

‏قبل الدمج لازم يكون فيه مكان كفاية **للنص القديم + النص الجديد + `\0`**.

## ‏Comparison — مقارنة النصوص

‏`strcmp(s1, s2)` بتقارن **محتوى الحروف**، مش عناوينها.

| الناتج | المعنى |
|---|---|
| `0` | ‏النصّان متساويان |
| ‏أقل من `0` | ‏النص الأول أصغر ترتيبًا من الثاني |
| ‏أكبر من `0` | ‏النص الأول أكبر ترتيبًا من الثاني |

‏`strncmp(s1, s2, n)` بتقارن بحد أقصى أول `n` حروف.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char a[] = "ITI";
    char b[] = "ITI";

    if (strcmp(a, b) == 0) {
        printf("Equal\n");
    }
    return 0;
}
```

> [!important] ‏مش `==` للمحتوى
> ‏لو `a` و`b` مصفوفتين، استخدام `a == b` بيقارن **عناوين بداية المصفوفتين**، مش الحروف الموجودة فيهم. استخدم `strcmp` لمقارنة النصوص.

## ‏Length — طول الـ String

‏`strlen(s)` بتحسب عدد الحروف **من غير `\0`**.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char word[] = "Hello";
    printf("%zu\n", strlen(word)); // 5
    printf("%zu\n", sizeof(word)); // 6
    return 0;
}
```

‏الفرق إن `sizeof(word)` بيحسب مساحة الـ Array كلها بالبايت، بينما `strlen(word)` بيمشي لحد ما يلاقي `\0`.

## ‏Searching — البحث داخل النص

| الدالة | الوظيفة |
|---|---|
| `strchr(s, c)` | ‏أول ظهور للحرف `c` |
| `strrchr(s, c)` | ‏آخر ظهور للحرف `c` |
| `strstr(s, sub)` | ‏أول ظهور لنص فرعي `sub` داخل `s` |

‏الدوال دي بترجع **Pointer** للمكان اللي لقيته، أو `NULL` لو مش موجود.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *msg = "Embedded C is fun";
    const char *pos = strstr(msg, "C");

    if (pos != NULL) {
        printf("Found: %s\n", pos); // C is fun
    }
    return 0;
}
```

## ‏Tokenizing — تقسيم النص

‏`strtok()` بتقسم String إلى أجزاء (**Tokens**) بناءً على فواصل تحددها، وبتعدّل النص الأصلي أثناء التشغيل.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char data[] = "red,green,blue";
    char *token = strtok(data, ",");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    return 0;
}
```

‏النتيجة: `red` ثم `green` ثم `blue`، كل واحدة في سطر.

> [!warning] ‏انتبه لـ `strtok`
> ‏لا تستخدمها مباشرةً على **String Literal** لأنها بتعدّل المحتوى. وكمان بتستخدم حالة داخلية؛ لو محتاج معالجة مستقلة متزامنة، لازم تختار بديل مناسب للمنصة.


> [!important] Understanding `strtok(NULL, ",")`
>
> الدالة `strtok()` بتستخدم علشان نقسم الـ **String** لأجزاء أصغر اسمها **Tokens** بناءً على فاصل معين (**Delimiter**).
>
> ```c
> token = strtok(NULL, ",");
> ```
>
> **شرح السطر:**
>
> - **`token`**: Pointer بيخزن عنوان بداية الـ Token الجديدة.
> - **`strtok()`**: الدالة المسؤولة عن تقسيم الـ String.
> - **`NULL`**: معناها كمّل من المكان اللي وقفت عنده في آخر استدعاء، مش ابدأ من الأول.
> - **`","`**: الفاصل المستخدم بين الكلمات هو الـ Comma.
>
> الدالة بترجع Pointer لأول حرف في الـ Token التالية، ولو مفيش Tokens تانية بترجع `NULL`.

### Practical Example

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char text[] = "Ahmed,Mohamed,Ali";

    char *token = strtok(text, ",");

    printf("%s\n", token);

    token = strtok(NULL, ",");
    printf("%s\n", token);

    token = strtok(NULL, ",");
    printf("%s\n", token);

    return 0;
}
```

**Output:**

```text
Ahmed
Mohamed
Ali
```

### Step-by-Step Explanation

1. أول استدعاء:

   `strtok(text, ",")`

   بيبدأ تقسيم الـ String ويرجع أول Token وهي `Ahmed`.

2. تاني استدعاء:

   `strtok(NULL, ",")`

   بيكمّل من آخر مكان وقف عنده ويرجع `Mohamed`.

3. تالت استدعاء:

   `strtok(NULL, ",")`

   بيرجع `Ali`.

4. لو استدعينا الدالة مرة كمان هترجع `NULL`، لأن مفيش Tokens متبقية.

> [!tip] Why Do We Use NULL?
>
> بنستخدم `NULL` علشان الدالة تحتفظ بمكان التقسيم السابق وتكمّل منه، بدل ما نبدأ تقسيم نفس الـ String من الأول كل مرة.
>
> وده مفيد جدًا لما نحتاج نقسم String فيها عدد غير معروف من الكلمات.

### Using `strtok()` With a While Loop

```c
char text[] = "C,Python,Java";

char *token = strtok(text, ",");

while (token != NULL)
{
    printf("%s\n", token);

    token = strtok(NULL, ",");
}
```

**الفكرة:**

- أول استدعاء بيجيب أول Token.
- الـ `while` بتفضل شغالة طول ما فيه Tokens.
- في كل Iteration بنستخدم `strtok(NULL, ",")` علشان نجيب الـ Token التالية.
- لما الدالة ترجع `NULL`، الـ Loop بتقف.

> [!warning] Important Notes
>
> - لازم تبدأ بـ `strtok(text, ",")` قبل ما تستخدم `strtok(NULL, ",")` لتكملة التقسيم.
> - الدالة بتعدّل الـ Original String وبتستبدل الـ Delimiters اللي بتلاقيها بـ `'\0'`.
> - استخدم Character Array قابلة للتعديل بدل String Literal.
> - الدالة بتتخطّى الفواصل المتكررة، وبالتالي مش بترجع Empty Tokens بينها.
> - `strtok()` بتحتفظ بحالة داخلية، لذلك مش مناسبة لتقسيم أكتر من String بالتداخل بالطريقة العادية.

> [!summary] Key Takeaway
>
> **`strtok(text, ",")`** → Start Tokenization.
>
> **`strtok(NULL, ",")`** → Get Next Token.
>
> **Return `NULL`** → No More Tokens.
## ‏Memory Operations — عمليات على البايتات

‏الدوال الجاية موجودة برضه في `string.h`، لكنها بتتعامل مع **عدد بايتات**، مش شرط C Strings.

| الدالة                   | المعنى                         | أهم نقطة                                      |
| ------------------------ | ------------------------------ | --------------------------------------------- |
| `memcpy(dest, src, n)`   | ‏نسخ `n` بايت                  | ‏المناطق **مينفعش تتداخل**                    |
| `memmove(dest, src, n)`  | ‏نسخ `n` بايت                  | ‏بتتعامل مع **الoverlapping** بأمان           |
| `memcmp(a, b, n)`        | ‏مقارنة أول `n` بايت           | ‏ناتج سالب/صفر/موجب                           |
| `memset(dest, value, n)` | ‏ملء `n` بايت بقيمة بايت معينة | ‏لا تضبط كل عنصر `int` إلى قيمة عددية عشوائية |

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char source[] = "ABCDE";
    char output[6];

    memcpy(output, source, sizeof(source));
    printf("%s\n", output); // ABCDE

    char data[] = "12345";
    memmove(data + 1, data, 4);
    printf("%s\n", data);   // 11234

    return 0;
}
```

‏في مثال `memmove`، مكان المصدر والوجهة **متداخلين**، ولذلك نستخدمها بدل `memcpy`.

### ‏`memset` مثال

```c
#include <string.h>

unsigned char buffer[16];
memset(buffer, 0, sizeof(buffer));
```

‏ده بيصفّر كل البايتات في الـ Buffer، ودي عملية شائعة لما نجهز مساحة استقبال بيانات.

> [!tip] ‏مقارنة سريعة: `strlen` و`sizeof` و`memcpy`
> ‏`strlen` تعد **الحروف لحد `\0`**، و`sizeof` يجيب **حجم النوع/الكائن بالبايت**، و`memcpy` ينسخ **العدد المحدد من البايتات حرفيًا**.

---

# ‏Pointers — فهم المؤشرات من الصفر

## ‏يعني إيه Pointer؟

‏الـ **Pointer** متغير بيحتفظ **بعنوان مكان في الذاكرة** بدل ما يحتفظ بالقيمة نفسها. ده سبب أهميته الكبيرة في Embedded C؛ لأن التعامل مع Buffers وMemory وHardware Registers محتاج فهم العناوين.

```c
int num = 10;
int *p = &num;
```

‏معناها:

- ‏`num` يحتوي القيمة `10`.
- ‏`&num` هو عنوان `num`.
- ‏`p` يحتفظ بالعنوان ده.
- ‏`*p` تقرأ أو تغيّر القيمة اللي موجودة عند العنوان.

```c
#include <stdio.h>

int main(void) {
    int num = 10;
    int *p = &num;

    printf("num = %d\n", num);
    printf("*p  = %d\n", *p);
    printf("p   = %p\n", (void *)p);

    *p = 25;
    printf("num = %d\n", num); // 25
    return 0;
}
```

‏`%p` مخصص لطباعة عنوان الذاكرة، وبنحوّل المؤشر إلى `(void *)` عشان الصيغة تبقى مناسبة.

### ‏إزاي تقرأ إعلان المؤشر؟

```c
int *p;       // p is a pointer to int
char *name;   // name is a pointer to char
float *fp;    // fp is a pointer to float
```

> [!warning] ‏`*` ليها دورين
> ‏في `int *p;` النجمة معناها **إعلان Pointer**. إنما في `x = *p;` معناها **Dereference** — الوصول للقيمة عند العنوان.

## ‏Pointer Size — حجم المؤشر

‏حجم الـ Pointer مش بيتحدد بنوع البيانات اللي بيشاور عليها، لكنه بيعتمد على **الـ Architecture / ABI / Compiler**.

| ‏البيئة الشائعة | ‏حجم Pointer المعتاد |
|---|---|
| ‏32-bit | ‏4 Bytes |
| ‏64-bit | ‏8 Bytes |

‏في بعض الـ Microcontrollers، الأحجام الفعلية ممكن تختلف حسب نموذج الذاكرة والـ Toolchain.

```c
#include <stdio.h>

int main(void) {
    printf("int*   = %zu\n", sizeof(int *));
    printf("char*  = %zu\n", sizeof(char *));
    printf("float* = %zu\n", sizeof(float *));
    return 0;
}
```

‏**احفظ الفرق:** ممكن كل المؤشرات دي يكون لها نفس الحجم على نفس المنصة، لكن الـ **Pointer Arithmetic** بيختلف حسب حجم العنصر اللي كل مؤشر بيشاور عليه.

---

# ‏Pointer Types — أنواع المؤشرات وأخطاء التعامل معاها

## ‏Null Pointer

‏مؤشر قيمته `NULL` معناه إنه **مش بيشاور على كائن صالح للاستخدام**.

```c
#include <stdio.h>

int main(void) {
    int *p = NULL;

    if (p != NULL) {
        printf("%d\n", *p);
    } else {
        printf("Pointer is NULL\n");
    }
    return 0;
}
```

‏بنستخدمه علشان نعبّر إن المؤشر لسه مش مرتبط بحاجة، أو إن عملية البحث/الحجز فشلت. لكن **محاولة `*p` لما `p == NULL` خطأ**.

## ‏Void Pointer — مؤشر عام

‏`void *` يقدر يحتفظ بعنوان كائن من أي Data Type، لكن لازم تحدد نوع البيانات قبل ما تعمل **Dereference**.

```c
#include <stdio.h>

int main(void) {
    int value = 10;
    void *p = &value;

    printf("%d\n", *(int *)p); // 10
    return 0;
}
```

‏تقدر تفكر فيها كده: `void *` يعرف **فين العنوان**، لكنه لوحده مش عارف **نوع القيمة** أو حجمها علشان يفسّرها.

## ‏Dangling Pointer — مؤشر لبيانات انتهى عمرها

‏ده Pointer كان بيشاور على مكان صالح، لكن المكان اتعمل له `free()` أو الكائن اللي كان بيشاور عليه انتهى عمره.

```c
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof *p);
    if (p == NULL) return 1;

    *p = 10;
    free(p);
    p = NULL;  // Avoid using the old dangling pointer
    return 0;
}
```

> [!warning] ‏مهم جدًا
> ‏ما تعملش `*p` بعد `free(p)`، وما ترجعش Pointer لمتغير محلي انتهى الـ Scope بتاعه. وتعيين `p = NULL` بيصلح **المؤشر ده فقط**؛ لو فيه Pointer تاني بيشاور على نفس الذاكرة هيفضل Dangling.

## ‏Wild Pointer — مؤشر غير مهيّأ

```c
int *p;  // Uninitialized: dangerous to dereference
```

‏ممكن يحتوي عنوان غير صالح أو قيمة غير معروفة؛ متستخدموش قبل ما تهيئه.

```c
int *p = NULL;  // Good starting state
```

## ‏Constant Pointer vs Pointer to Constant

‏ترتيب كلمة `const` والنجمة بيفرّق جدًا:

| التعريف | تقدر تغيّر العنوان المخزّن؟ | تقدر تغيّر القيمة عبر المؤشر؟ |
|---|---|---|
| `int *p` | ‏أيوه | ‏أيوه |
| `int *const p = &a` | ‏لأ | ‏أيوه |
| `const int *p = &a` | ‏أيوه | ‏لأ |
| `const int *const p = &a` | ‏لأ | ‏لأ |

### ‏Constant Pointer

```c
int a = 10;
int b = 20;
int *const p = &a;

*p = 15;  // Allowed
// p = &b; // Compile error
```

‏العنوان نفسه **ثابت**، لكن تقدر تعدّل القيمة اللي موجودة فيه.

### ‏Pointer to Constant

```c
int a = 10;
int b = 20;
const int *p = &a;

p = &b;   // Allowed
// *p = 30; // Compile error
```

‏المؤشر ممكن يتحرك، لكن مينفعش تعدّل القيمة **من خلاله**.

> [!tip] ‏طريقة للحفظ
> ‏`const` ناحية **البيانات** = ممنوع تعديل البيانات عبر المؤشر. ‏`const` ناحية **المؤشر نفسه** = ممنوع تغيّر العنوان المخزّن.

## ‏Function Pointer

‏ده نوع Pointer مختلف: بدل ما يشاور على متغير، بيحتفظ بعنوان **Function**. هنستخدمه بالتفصيل في قسم التطبيقات المتقدمة.

---
# ‏Pointer Arithmetic — الحساب بالمؤشرات

## ‏Increment / Decrement

‏لما تكتب `p++` لمؤشر نوعه `int *`، هو مش بيتحرك بايت واحد؛ هو بيتحرك **بمقدار عنصر كامل** من النوع اللي بيشاور عليه.

```c
#include <stdio.h>

int main(void) {
    int arr[] = {10, 20, 30};
    int *p = arr;

    printf("%d\n", *p); // 10
    p++;
    printf("%d\n", *p); // 20
    p--;
    printf("%d\n", *p); // 10
    return 0;
}
```

‏لو حجم `int` عندك أربعة بايت، `p++` هينقل العنوان أربعة بايت. لو نوع المؤشر `char *`، خطوة واحدة معناها حجم عنصر `char` واحد.

## ‏Pointer + Number

‏`p + n` معناها الانتقال `n` **عناصر** للأمام، و`p - n` معناها الرجوع `n` عناصر للخلف.

```c
#include <stdio.h>

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    printf("%d\n", *(p + 2)); // 30
    printf("%d\n", *(p + 4)); // 50
    return 0;
}
```

‏لاحظ إن:

```c
arr[2] == *(arr + 2)
```

‏ده بيوضح العلاقة القوية بين الـ **Arrays** والـ **Pointers**.

## ‏Pointer - Pointer

‏تقدر تطرح مؤشرين من بعض لما يكونوا بيشاوروا على عناصر من **نفس المصفوفة** (أو الموضع التالي لآخر عنصر). الناتج هو **عدد العناصر بينهم**، مش عدد البايتات.

```c
#include <stdio.h>
#include <stddef.h>

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *first = &arr[1];
    int *last  = &arr[4];

    ptrdiff_t difference = last - first;
    printf("Difference = %td\n", difference); // 3
    return 0;
}
```

‏نوع ناتج طرح المؤشرات اسمه `ptrdiff_t` من `stddef.h`.

## ‏Comparing Pointers

‏تقدر تقارن بين مواقع مؤشرات داخل نفس المصفوفة علشان تعرف أي عنصر سابق التاني في الذاكرة.

```c
int arr[] = {10, 20, 30};
int *p = &arr[0];
int *q = &arr[2];

if (p < q) {
    // p points to an earlier array element
}
```

‏كمان `==` و`!=` بيستخدموا لمعرفة هل المؤشرين متساويين في العنوان ولا لأ. لكن المقارنات الترتيبية زي `<` و`>` ملهاش معنى عام مضمون بين كائنات منفصلة لا تربطها نفس المصفوفة.

> [!warning] ‏قاعدة الأمان
> ‏الحساب بالمؤشر لازم يفضل داخل حدود نفس الـ Array، أو عند **one-past-the-end** من غير ما تعمل Dereference للمكان ده. تجاوز الحدود ممكن يسبب **Undefined Behavior**.

---

# ‏Dynamic Memory Allocation — حجز الذاكرة وقت التشغيل

## ‏ليه نحتاج Dynamic Allocation؟

‏أحيانًا حجم البيانات مش معروف وقت كتابة البرنامج. مثلًا هتقرأ عدد عناصر من المستخدم أو من Sensor، وسعتها مش ثابتة. في الحالة دي بنستخدم **Heap** لحجز مساحة وقت التشغيل (**Runtime**).

‏المحاضرة ركزت على أربع دوال موجودة في `stdlib.h`:

| الدالة | الوظيفة |
|---|---|
| `malloc(bytes)` | ‏حجز عدد من البايتات **من غير تهيئة محتواها** |
| `calloc(count, size)` | ‏حجز مساحة لعناصر، مع **تصفير البايتات** |
| `realloc(ptr, new_size)` | ‏تغيير حجم حجز موجود |
| `free(ptr)` | ‏تحرير المساحة المحجوزة |

‏بشكل عام، `malloc` و`calloc` و`realloc` بترجع مؤشر للمساحة، أو `NULL` لو الحجز فشل.

## ‏`malloc` — حجز مساحة من الـ Heap

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int count = 5;
    int *arr = malloc(count * sizeof *arr);

    if (arr == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        arr[i] = i * 10;
        printf("%d ", arr[i]);
    }

    free(arr);
    arr = NULL;
    return 0;
}
```

‏التتبع:

1. ‏`sizeof *arr` هو حجم عنصر `int` واحد، بافتراض النوع ده.
2. ‏بنضرب الحجم في عدد العناصر `count`.
3. ‏`malloc()` بتحجز مساحة من الـ Heap، وممكن ترجع `NULL`.
4. ‏لازم **نهيّئ العناصر** قبل استخدام قيمها لأن `malloc` مش بتصفّرها.
5. ‏بنستدعي `free()` بعد انتهاء الحاجة للمساحة.

> [!important] ‏ليه `sizeof *arr` حلوة؟
> ‏بدل `malloc(5 * sizeof(int))`، كتابة `malloc(5 * sizeof *arr)` بتخلّي حجم العنصر مرتبطًا بنوع المؤشر، فتقل الأخطاء لو غيّرت النوع بعدين.

## ‏`calloc` — حجز مع تصفير البايتات

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = calloc(5, sizeof *arr);
    if (arr == NULL) return 1;

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]); // 0 0 0 0 0
    }

    free(arr);
    return 0;
}
```

‏الفرق الأساسي من `malloc`: الـ **`calloc` بتصفّر كل البايتات المحجوزة**. في المثال ده النتيجة أصفار للعناصر الصحيحة.

## ‏`realloc` — تكبير أو تصغير مساحة

‏لو حجزت مكان لخمس عناصر وبعدين اكتشفت إنك محتاج عشرة، تقدر تحاول تغيّر الحجم بـ `realloc`.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(5 * sizeof *arr);
    if (arr == NULL) return 1;

    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    int *temp = realloc(arr, 10 * sizeof *arr);
    if (temp == NULL) {
        free(arr);       // Original allocation still exists
        return 1;
    }
    arr = temp;

    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1;  // Initialize the new elements
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
```

‏ممكن `realloc` توسّع نفس المكان، أو تنقل البيانات لمكان جديد. عشان كده **عنوان الـ Pointer نفسه ممكن يتغيّر**.

> [!warning] ‏غلط خطير في `realloc`
> ‏متكتبش مباشرةً `arr = realloc(arr, new_size);` لو مش هتتعامل مع الفشل؛ لأن لو رجعت `NULL` هتفقد عنوان الحجز القديم وتعمل **Memory Leak**. استخدم Pointer مؤقت زي `temp` وبعدين حدث `arr` عند النجاح.

## ‏`free` — تحرير الحجز

‏كل حجز ناجح في النهاية لازم يكون له تحرير مناسب. بعد `free` الذاكرة مبقتش ملكك؛ استخدام العنوان القديم يؤدي إلى **Use-after-free**.

```c
int *p = malloc(sizeof *p);
if (p != NULL) {
    *p = 42;
    free(p);
    p = NULL;
}
```

### ‏أخطاء الذاكرة الشائعة

| المشكلة | معناها | إزاي تتجنبها؟ |
|---|---|---|
| ‏**Memory Leak** | ‏حجز الذاكرة من غير تحريرها | ‏استخدم `free` في الوقت المناسب |
| ‏**Use-after-free** | ‏قراءة/كتابة في مساحة اتحررت | ‏متستخدمش Pointer بعد `free` |
| ‏**Double Free** | ‏تحرير نفس الحجز مرتين | ‏نظّم ملكية الذاكرة وما تكررش `free` |
| ‏**Uninitialized Memory** | ‏قراءة محتوى `malloc` قبل التهيئة | ‏اكتب القيم أولًا أو استخدم `calloc` |
| ‏**Out of Bounds** | ‏الوصول خارج المساحة المطلوبة | ‏راقب عدد العناصر والحجم |
| ‏**Lost Pointer** | ‏فقدان آخر عنوان للحجز | ‏احتفظ بعنوان الحجز لحد ما تحرره |

> [!warning] ‏في Embedded Systems
> ‏الـ Heap مش دايمًا متاح أو مناسب. Dynamic Allocation ممكن يسبب **Fragmentation**، وسلوك وقت التنفيذ ممكن يصعب توقعه. عشان كده بعض المشاريع اللي فيها **Real-time Constraints** بتفضّل Static Buffers أو Memory Pools. ده توضيح تطبيقي للفكرة، مش بديل عن فهم الأربع دوال.

---

# ‏Advanced Pointer Applications — استخدامات متقدمة

## ‏Access Array Elements with Pointers

‏بما إن اسم الـ Array بيتحوّل لعنوان أول عنصر في تعبيرات كثيرة، تقدر تستخدم Pointer علشان تلف على العناصر:

```c
#include <stdio.h>

int main(void) {
    int numbers[] = {10, 20, 30, 40};
    int *p = numbers;

    for (int i = 0; i < 4; i++) {
        printf("%d ", *(p + i));
    }
    return 0;
}
```

‏المعادلة المفيدة هنا: `p[i]` تساوي `*(p + i)`.

## ‏Array of Pointers — مصفوفة مؤشرات

‏بدل مصفوفة فيها أرقام مباشرةً، ممكن تعمل مصفوفة كل عنصر فيها **عنوان متغير**:

```c
#include <stdio.h>

int main(void) {
    int a = 10, b = 20, c = 30;
    int *ptrs[3] = {&a, &b, &c};

    for (int i = 0; i < 3; i++) {
        printf("%d ", *ptrs[i]);
    }
    return 0;
}
```

‏`ptrs[0]` هو Pointer، و`*ptrs[0]` هي القيمة اللي بيشاور عليها؛ هنا `10`.

### ‏Array of String Pointers

```c
#include <stdio.h>

int main(void) {
    const char *names[] = {"Ali", "Omar", "Mona"};

    for (int i = 0; i < 3; i++) {
        printf("%s\n", names[i]);
    }
    return 0;
}
```

‏مناسب جدًا للقوائم الثابتة ورسائل المستخدم والقيم الوصفية.

## ‏Double Pointer — مؤشر لمؤشر

‏الـ **Double Pointer** من نوع `int **` بيحتفظ بعنوان Pointer تاني، والمؤشر التاني بيحتفظ بعنوان القيمة.

```c
#include <stdio.h>

int main(void) {
    int a = 10;
    int *p = &a;
    int **pp = &p;

    printf("%d\n", a);    // 10
    printf("%d\n", *p);   // 10
    printf("%d\n", **pp); // 10

    **pp = 50;
    printf("%d\n", a);    // 50
    return 0;
}
```

‏السلسلة دي بتوضح شكل العلاقة:

```text
pp   ----->   p   ----->   a
                address     value = 10

*pp  = p
**pp = a
```

‏ليه نحتاج `**`؟ مثلًا لو عايز Function **تغيّر المؤشر الأصلي نفسه**؛ تبعت لها عنوانه، فيبقى Parameter من نوع Pointer to Pointer.

```c
#include <stdlib.h>

int create_buffer(int **out, size_t count) {
    if (out == NULL) return 0;

    int *buffer = malloc(count * sizeof *buffer);
    if (buffer == NULL) return 0;

    *out = buffer;
    return 1;
}
```

‏الـ Caller يقدر يمرر `&my_pointer`؛ والدالة تكتب عنوان الحجز الجديد داخل المؤشر الأصلي من خلال `*out`.

## ‏Function Pointers — مؤشر إلى دالة

‏الـ Function Pointer بيخزّن عنوان دالة ذات **Return Type** و**Parameters** محددين.

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main(void) {
    int (*operation)(int, int) = add;

    printf("%d\n", operation(5, 7)); // 12
    return 0;
}
```

‏اقرأ السطر ده بالراحة:

```c
int (*operation)(int, int);
```

- ‏`operation` اسم الـ Pointer.
- ‏الـ `(*operation)` معناها ده **مؤشر لدالة**.
- ‏`(int, int)` معناها الدالة تستقبل اتنين `int`.
- ‏`int` في البداية معناها الدالة بترجع `int`.

> [!important] ‏ليه الأقواس مهمة؟
> ‏`int (*p)(int, int)` ده **Pointer to Function**، لكن `int *p(int, int)` ده إعلان **Function بترجع Pointer to int**. فرق صغير في الأقواس بيغيّر المعنى تمامًا.

### ‏`typedef` لتسهيل الشكل

```c
typedef int (*Operation)(int, int);

int add(int a, int b) {
    return a + b;
}

Operation op = add;
```

‏ده بيخلي تعريف Function Pointers الطويل سهل القراءة.

## ‏Callbacks — استخدام عملي

‏المحاضرة وضحت إن الدالة تقدر تستقبل Callback تختار بناءً عليها طريقة معالجة الأرقام، زي **Square** أو **Double**.

```c
#include <stdio.h>

typedef int (*Transform)(int);

int square(int n) { return n * n; }
int twice(int n)  { return 2 * n; }

void apply(const int arr[], int length, Transform fn) {
    for (int i = 0; i < length; i++) {
        printf("%d ", fn(arr[i]));
    }
    printf("\n");
}

int main(void) {
    int nums[] = {1, 2, 3};
    apply(nums, 3, square);  // 1 4 9
    apply(nums, 3, twice);   // 2 4 6
    return 0;
}
```

‏في Embedded ممكن تلاقي الفكرة دي في APIs بتستقبل دالة تتنفذ لما **Event** يحصل. بس لازم تعرف إن تسجيل Callback وتنفيذها وتوقيت التنفيذ بيعتمدوا على المكتبة أو الـ Driver نفسه.

## ‏Array of Function Pointers

‏ممكن تخزّن أكتر من Function Pointer داخل Array طالما ليهم **نفس الـ Signature**، وبعدها تختار الدالة اللي هتنفّذها حسب الـ Index.

```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    int (*operations[3])(int, int) = {add, sub, mul};

    printf("%d\n", operations[0](6, 2)); // 8
    printf("%d\n", operations[1](6, 2)); // 4
    printf("%d\n", operations[2](6, 2)); // 12
    return 0;
}
```

‏استخدامات الفكرة: **Menus، Dispatch Tables، State Machines**، واختيار العملية المطلوبة بدل كتابة سلسلة طويلة من الشروط في بعض الحالات.

## ‏Passing Pointers to Functions — الفوائد

‏تمريرة الـ Pointer مفيدة في تلات حاجات محورية:

1. ‏**Efficiency:** ‏بدل نسخ كمية بيانات كبيرة، تمرّر عنوانها.
2. ‏**Modification:** ‏تسمح للدالة تعدّل القيم الأصلية عند الحاجة.
3. ‏**Data Sharing:** ‏تخلي دوال مختلفة توصل لنفس الـ Buffer أو البيانات.

‏وده مش معناه نسيب الحدود والأمان: الدالة غالبًا محتاجة تستقبل **العنوان + الحجم**، ولو مش هتعدّل البيانات الأفضل تعلنها `const`.

```c
#include <stddef.h>

int sum_values(const int *data, size_t count) {
    int total = 0;
    for (size_t i = 0; i < count; i++) {
        total += data[i];
    }
    return total;
}
```

## ‏Return Pointer from Function — إرجاع مؤشر من دالة

‏المحاضرة عرضت ثلاث طرق صحيحة، وطريقة واحدة لازم تمنعها:

### ‏إرجاع Pointer لمساحة Dynamic

```c
#include <stdlib.h>

int *make_value(void) {
    int *p = malloc(sizeof *p);
    if (p != NULL) {
        *p = 42;
    }
    return p;
}

int main(void) {
    int *value = make_value();
    if (value == NULL) return 1;

    free(value);  // Caller owns the allocated memory
    return 0;
}
```

‏المساحة بتفضل موجودة بعد انتهاء الدالة، لكن المسؤولية على الـ Caller إنه يعمل `free`.

### ‏إرجاع Pointer لمتغير `static` محلي

```c
int *get_counter(void) {
    static int counter = 0;
    counter++;
    return &counter;
}
```

‏المتغير `static` عمره مستمر طوال تشغيل البرنامج، فالعنوان يفضل صالحًا.

### ‏إرجاع نفس الـ Pointer اللي استقبلته الدالة

```c
int *increment_each(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i]++;
    }
    return arr;
}
```

‏ده آمن **لو المصفوفة الأصلية ما زالت صالحة** بعد الاستدعاء، لأن الدالة مش بتعمل Buffer مؤقت وانتهى عمره.

### ‏الطريقة الممنوعة — إرجاع عنوان Local Variable

```c
int *wrong_function(void) {
    int x = 10;
    return &x;  // WRONG: x stops existing after return
}
```

> [!danger] ‏ممنوع تستخدم العنوان ده
> ‏`x` متغير محلي عادي، وعمره بينتهي عند نهاية الدالة؛ المؤشر اللي رجعته بقى **Dangling Pointer**، وDereference ليه سلوك غير معرّف.

## ‏Returning Multiple Values Using Pointers

‏الدالة في C بتقدر ترجع قيمة مباشرة واحدة بـ `return`، لكن ممكن «ترجع» نتائج إضافية عبر مؤشرات بتتكتب فيها النتائج.

‏مثلًا نحسب **المساحة والمحيط** في استدعاء واحد:

```c
#include <stdio.h>

void rectangle(int length, int width, int *area, int *perimeter) {
    *area = length * width;
    *perimeter = 2 * (length + width);
}

int main(void) {
    int area = 0;
    int perimeter = 0;

    rectangle(10, 5, &area, &perimeter);
    printf("Area = %d\n", area);           // 50
    printf("Perimeter = %d\n", perimeter); // 30
    return 0;
}
```

‏الـ Parameters `area` و`perimeter` بيشاوروا على متغيرات موجودة عند الـ Caller؛ فبالتالي تغيير `*area` و`*perimeter` بيظهر خارج الدالة.

## ‏Character Pointers — مؤشرات الحروف والنصوص

‏في الجزء الأخير من المحتوى، التركيز على الفرق بين مؤشر لحرف، ومؤشر لنص، ومصفوفة حروف.

```c
char ch = 'A';
char *p1 = &ch;

char word[] = "Hello";
char *p2 = word;

const char *p3 = "Hello";
```

- ‏`p1` بيشاور على متغير من نوع `char`.
- ‏`p2` بيشاور على أول حرف في **مصفوفة قابلة للتعديل**.
- ‏`p3` بيشاور على **String Literal**، فلازم نتعامل مع محتواها على إنها غير قابلة للتعديل.

```c
#include <stdio.h>

int main(void) {
    char word[] = "Hello";
    char *modifiable = word;
    const char *message = "World";

    modifiable[0] = 'Y';
    printf("%s\n", word);     // Yello
    printf("%s\n", message);  // World

    // message[0] = 'M';  // Not allowed
    return 0;
}
```

> [!warning] ‏`char *p = "Hello";`
> ‏الشكل ده ممكن تشوفه في أمثلة C، لكن **تعديل الـ String Literal من خلال `p` سلوك غير معرّف**. الأفضل تكتب `const char *p = "Hello";` لو النص ثابت، أو `char p[] = "Hello";` لو عايز تعدّل الحروف.

---

# ‏Revision and Practice — مراجعة وتدريبات

## ‏جدول مقارنة سريع قبل الامتحان

| ‏المفهوم | ‏القاعدة الأساسية | ‏أشهر غلطة |
|---|---|---|
| ‏Function Declaration | ‏إخبار الـ Compiler بشكل الدالة | ‏استدعاء الدالة قبل ما يعرف الـ Prototype |
| ‏Call by Value | ‏الدالة تستقبل نسخة | ‏تتوقع إن المتغير الأصلي هيتغير |
| ‏Call by Address | ‏تمرّر العنوان باستخدام `&` | ‏تنسى `*` وقت التعديل |
| ‏Recursion | ‏دالة تنادي نفسها | ‏نسيان Base Case |
| ‏Array | ‏عناصر من نوع واحد ومتصلة في الذاكرة | ‏استخدام Index خارج النطاق |
| ‏Array Parameter | ‏بتتحول لمؤشر لأول عنصر | ‏تفتكر `sizeof` عليها هيجيب حجم المصفوفة كلها |
| ‏String | ‏مصفوفة `char` تنتهي بـ `\0` | ‏نسيان مكان `\0` |
| ‏`strcpy` / `strcat` | ‏تحتاج مساحة كفاية في الوجهة | ‏Buffer Overflow |
| ‏`strncpy` | ‏قد لا تضيف `\0` | ‏تتعامل مع الناتج كنص صالح دائمًا |
| ‏`strcmp` | ‏مقارنة محتوى النص | ‏استخدام `==` |
| ‏Pointer | ‏يحمل عنوانًا | ‏Dereference لمؤشر غير صالح |
| ‏`int *const p` | ‏العنوان المخزّن ثابت | ‏الخلط مع Pointer to Constant |
| ‏`const int *p` | ‏القيمة غير قابلة للتعديل من خلاله | ‏الخلط مع Constant Pointer |
| ‏`p++` | ‏تحرك بمقدار عنصر من النوع | ‏تفتكرها بايت واحد دائمًا |
| ‏`malloc` | ‏يحجز مساحة غير مهيّأة | ‏تقرأها قبل ما تكتب فيها |
| ‏`calloc` | ‏يحجز ويصفّر البايتات | ‏تنسى اختبار `NULL` |
| ‏`realloc` | ‏ممكن يغيّر مكان الحجز | ‏تفقد المؤشر القديم عند الفشل |
| ‏`free` | ‏يحرر الحجز | ‏Use-after-free / Double Free |
| ‏Double Pointer | ‏عنوان Pointer آخر | ‏الخلط بين `*p` و`**pp` |
| ‏Function Pointer | ‏عنوان Function | ‏نسيان الأقواس في الإعلان |
| ‏Return Pointer | ‏لازم البيانات تفضل عايشة | ‏ترجع عنوان Local Variable |

## ‏أسئلة فهم سريعة

**س: ليه `change(a)` غالبًا مش بيغيّر `a`، بينما `change(&a)` ممكن تغيّره؟**  
‏ج: الأول بيبعت نسخة من **القيمة**، والثاني بيبعت نسخة من **العنوان**؛ وباستخدام Dereference في الدالة نقدر نعدّل الأصل.

**س: إيه الفرق بين `arr[2]` و`*(arr + 2)`؟**  
‏ج: في المصفوفات العادية الاتنين بيعبروا عن نفس العنصر.

**س: ليه `sizeof(arr)` ممكن يبقى مختلف عن `sizeof(pointer)`؟**  
‏ج: الـ Array الحقيقية بتخزن كل العناصر، بينما الـ Pointer بيخزن عنوانًا فقط.

**س: امتى أستخدم `memmove` بدل `memcpy`؟**  
‏ج: لو منطقتا المصدر والوجهة **متداخلتين**.

**س: إيه الفرق بين `char text[] = "Hi";` و`const char *text = "Hi";`؟**  
‏ج: الأول Array حروف قابلة للتعديل، والثاني مؤشر إلى String Literal تعاملها كنص للقراءة فقط.

**س: ليه `realloc` محتاجة Pointer مؤقت؟**  
‏ج: لأن فشلها بيرجع `NULL` مع بقاء الحجز القديم؛ لو ضيّعت عنوانه مش هتعرف تحرره.

**س: إيه اللي يخلي Function Pointer مختلف عن Pointer عادي؟**  
‏ج: الأول بيحتفظ بعنوان Function ويمكن استدعاؤها عن طريقه، والثاني عادةً بيشاور على كائن/بيانات.

## ‏تدريبات عملية من موضوعات المحاضرة

‏التمارين التالية مبنية على قائمة التدريب الموجودة في المحتوى؛ ابدأ تحاول تحل قبل ما تبص على أي حل:

- [ ] ‏اقرأ `n` أعداد داخل Array واطبعهم **بالعكس**.
- [ ] ‏انسخ عناصر Array داخل Array تانية.
- [ ] ‏احسب **عدد العناصر المكررة** في Array، وحدد معنى «المكرر» قبل الحل: عدد القيم المختلفة المكررة ولا إجمالي التكرارات الزائدة.
- [ ] ‏اطبع العناصر **Unique** فقط.
- [ ] ‏احسب **Frequency** لكل عنصر.
- [ ] ‏طلع أكبر وأصغر قيمة داخل Array.
- [ ] ‏رتّب Array تصاعديًا، وبعدها تنازليًا.
- [ ] ‏حوّل عددًا عشريًا إلى تمثيل **Binary**.
- [ ] ‏احسب عدد الكلمات داخل String.
- [ ] ‏احسب طول String **من غير `strlen`**.
- [ ] ‏قارن بين Stringين **من غير `strcmp`**.
- [ ] ‏انسخ String يدويًا من غير `strcpy`.
- [ ] ‏اقرأ جملة، وبدّل الحروف الصغيرة لكبيرة والعكس.

### ‏تطبيق محلول — عكس مصفوفة

```c
#include <stdio.h>

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    return 0;
}
```

‏الفكرة إننا بنبدأ من آخر Index وهو `n - 1` ونفضل ننقص لحد `0`.

### ‏تطبيق محلول — طول String من غير Library Function

```c
#include <stdio.h>

int string_length(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    printf("%d\n", string_length("Embedded")); // 8
    return 0;
}
```

‏إحنا بنعد لحد الـ Null Terminator، ومش بنحسبه ضمن الطول.

### ‏تطبيق محلول — استخراج أكبر وأصغر عنصر

```c
#include <stdio.h>

int main(void) {
    int arr[] = {8, 3, 19, 6, 12};
    int size = 5;
    int minimum = arr[0];
    int maximum = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < minimum) minimum = arr[i];
        if (arr[i] > maximum) maximum = arr[i];
    }

    printf("Min=%d, Max=%d\n", minimum, maximum);
    return 0;
}
```

‏خد بالك إننا افترضنا الـ Array **مش فاضية**، وإلا مينفعش نبدأ بـ `arr[0]`.

## ‏أسئلة Output مهم تحلها بنفسك

### ‏تحدي: إيه الناتج؟

```c
#include <stdio.h>

void update(int x, int *y) {
    x += 10;
    *y += 10;
}

int main(void) {
    int a = 5, b = 5;
    update(a, &b);
    printf("%d %d\n", a, b);
    return 0;
}
```

> [!note]- ‏شوف الإجابة بعد المحاولة
> ‏الناتج `5 15`؛ لأن `x` نسخة من `a`، لكن `y` شايل عنوان `b`.

### ‏تحدي: Pointer Arithmetic

```c
#include <stdio.h>

int main(void) {
    int a[] = {3, 6, 9, 12};
    int *p = a;
    p += 2;
    printf("%d %d\n", *p, *(p - 1));
    return 0;
}
```

> [!note]- ‏شوف الإجابة بعد المحاولة
> ‏الناتج `9 6`؛ لأن `p` اتحرك للعنصر `a[2]`، و`p - 1` بيرجع للعنصر `a[1]`.

### ‏تحدي: `static` Function Variable

```c
#include <stdio.h>

int next_value(void) {
    static int x = 0;
    return ++x;
}

int main(void) {
    printf("%d ", next_value());
    printf("%d\n", next_value());
    return 0;
}
```

> [!note]- ‏شوف الإجابة بعد المحاولة
> ‏الناتج `1 2`؛ لأن `static` بتحافظ على قيمة `x` بين الاستدعاءات.

---

## ‏الخلاصة اللي لازم تثبت في دماغك

> [!summary] ‏أهم الأفكار
> ‏**Functions** بتنظّم البرنامج، و**Pointers** بتخليك تتحكم في البيانات عن طريق عناوينها.  
> ‏**Arrays** عناصرها متجاورة في الذاكرة، و**Strings** هي Arrays من `char` تنتهي بـ `\0`.  
> ‏**Function Pointers** أساس الـ Callbacks، و**Double Pointers** مفيدة لما تحتاج تغيّر Pointer من داخل Function.  
> ‏**Dynamic Allocation** قوية، لكن لازم تدير الحجز والحدود والتحرير بعناية عشان تمنع Memory Leaks وDangling Pointers.

‏**ترتيب مذاكرة مقترح:** افهم أولًا `&` و`*` وCall by Value، وبعدها Arrays، ثم العلاقة بين Arrays وPointers، ثم Strings، وبعدها Function Pointers وDynamic Memory. كل مفهوم جديد هنا مبني على اللي قبله.






