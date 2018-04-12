# Conformance of CAJUN (C++)

## 1. Parse Validation

* `../data/jsonchecker/fail13.json` is invalid but was mistakenly deemed valid.
~~~js
{"Numbers cannot have leading zeroes": 013}
~~~

* `../data/jsonchecker/fail25.json` is invalid but was mistakenly deemed valid.
~~~js
["	tab	character	in	string	"]
~~~

* `../data/jsonchecker/fail27.json` is invalid but was mistakenly deemed valid.
~~~js
["line
break"]
~~~

* `../data/jsonchecker/fail29.json` is invalid but was mistakenly deemed valid.
~~~js
[0e]
~~~

* `../data/jsonchecker/fail30.json` is invalid but was mistakenly deemed valid.
~~~js
[0e+]
~~~


Summary: 29 of 34 are correct.

## 2. Parse Double


Summary: 66 of 66 are correct.

## 3. Parse String

* `["\uD834\uDD1E"]`
  * expect: `"ùÑû"` (length: 4)
  * actual: `"Ì†¥Ì¥û"` (length: 6)


Summary: 8 of 9 are correct.

## 4. Roundtrip

* Fail:
~~~js
{"foo":"bar"}
~~~

~~~js
{
	"foo" : "bar"
}
~~~

* Fail:
~~~js
{"a":null,"foo":"bar"}
~~~

~~~js
{
	"a" : null,
	"foo" : "bar"
}
~~~

* Fail:
~~~js
[-1234567890123456789]
~~~

~~~js
[
	-1234567890123456768
]
~~~

* Fail:
~~~js
[1234567890123456789]
~~~

~~~js
[
	1234567890123456768
]
~~~

* Fail:
~~~js
[9223372036854775807]
~~~

~~~js
[
	9223372036854775808
]
~~~

* Fail:
~~~js
[0.0]
~~~

~~~js
[
	0
]
~~~

* Fail:
~~~js
[-0.0]
~~~

~~~js
[
	-0
]
~~~

* Fail:
~~~js
[1.2345]
~~~

~~~js
[
	1.2344999999999999307
]
~~~

* Fail:
~~~js
[-1.2345]
~~~

~~~js
[
	-1.2344999999999999307
]
~~~

* Fail:
~~~js
[5e-324]
~~~

~~~js
[
	4.9406564584124654418e-324
]
~~~

* Fail:
~~~js
[2.225073858507201e-308]
~~~

~~~js
[
	2.225073858507200889e-308
]
~~~

* Fail:
~~~js
[2.2250738585072014e-308]
~~~

~~~js
[
	2.2250738585072013831e-308
]
~~~

* Fail:
~~~js
[1.7976931348623157e308]
~~~

~~~js
[
	1.7976931348623157081e+308
]
~~~


Summary: 14 of 27 are correct.

