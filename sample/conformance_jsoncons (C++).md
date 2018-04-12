# Conformance of jsoncons (C++)

## 1. Parse Validation


Summary: 34 of 34 are correct.

## 2. Parse Double


Summary: 66 of 66 are correct.

## 3. Parse String


Summary: 9 of 9 are correct.

## 4. Roundtrip

* Fail:
~~~js
{"foo":"bar"}
~~~

~~~js
{"foo": "bar"}
~~~

* Fail:
~~~js
{"a":null,"foo":"bar"}
~~~

~~~js
{"a": null,"foo": "bar"}
~~~

* Fail:
~~~js
[-9223372036854775808]
~~~

~~~js
[-9223372036854775808.0]
~~~

* Fail:
~~~js
[5e-324]
~~~

~~~js
[4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954e-324]
~~~

* Fail:
~~~js
[1.7976931348623157e308]
~~~

~~~js
[1.7976931348623157e+308]
~~~


Summary: 22 of 27 are correct.

