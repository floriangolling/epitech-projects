import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class Register extends StatefulWidget {
  const Register({Key? key}) : super(key: key);

  @override
  State<Register> createState() => _RegisterState();
}

class _RegisterState extends State<Register> {
  final _formKey = GlobalKey<FormState>();
  final _passwordController = TextEditingController();
  late String _email;
  late String _password;

  Widget _buildLogoImage() {
    return Image.asset(
      'images/area_logo.png',
      width: 125,
      height: 125,
    );
  }

  bool isEmail(String value) {
    return value.isNotEmpty && value.length >= 3;
  }

  Widget _buildEnterEmail() {
    return SizedBox(
        width: 275,
        child: TextFormField(
          validator: (value) =>
              !isEmail(value!) ? "Enter a valid username." : null,
          onSaved: (value) {
            _email = value!;
          },
          decoration: const InputDecoration(
            border: OutlineInputBorder(),
            hintText: 'Enter a username',
          ),
        ));
  }

  Widget _buildPassword() {
    return SizedBox(
        width: 275,
        child: TextFormField(
          obscureText: true,
          controller: _passwordController,
          validator: (value) => value!.isEmpty || value.length < 6
              ? "Password must be at least 6 characters."
              : null,
          onSaved: (value) {
            _password = value!;
          },
          decoration: const InputDecoration(
            border: OutlineInputBorder(),
            hintText: 'Enter a password',
          ),
        ));
  }

  Widget _buildRepeatPassword() {
    return SizedBox(
        width: 275,
        child: TextFormField(
          obscureText: true,
          validator: (value) => value!.isEmpty ||
                  (value.isNotEmpty && value != _passwordController.text)
              ? "Must match the previous entry."
              : null,
          decoration: const InputDecoration(
            border: OutlineInputBorder(),
            hintText: 'Repeat password',
          ),
        ));
  }

  Widget _buildSignUp() {
    return ElevatedButton(
        child: const Text('Sign up'),
        style: ElevatedButton.styleFrom(
            primary: Colors.black,
            padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 15),
            textStyle:
                const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
        onPressed: () async {
          if (_formKey.currentState!.validate()) {
            final FormState? form = _formKey.currentState;
            form!.save();
            final response = await execRegister();
            if (response) {
              Navigator.of(context)
                  .pushNamedAndRemoveUntil(
                      '/login', (Route<dynamic> route) => false)
                  .then((_) => setState(() {}));
            }
            _formKey.currentState?.reset();
            FocusScope.of(context).unfocus();
          }
        });
  }

  Future<bool> execRegister() async {
    final response = await http.post(
      Uri.parse('http://10.0.2.2:8080/register'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'username': _email,
        "password": _password,
      }),
    );
    if (response.statusCode == 200) {
      return (true);
    } else {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
        content: Text("An error occured, please try again"),
      ));
      return (false);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          iconTheme: const IconThemeData(
            color: Colors.black, //change your color here
          ),
          title: const Text('Sign up', style: TextStyle(color: Colors.black)),
          backgroundColor: Colors.white,
        ),
        backgroundColor: const Color(0xffffffff),
        body: SafeArea(
            child: Form(
                key: _formKey,
                child: Container(
                    alignment: Alignment.center,
                    child: SingleChildScrollView(
                        child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: <Widget>[
                        _buildLogoImage(),
                        const SizedBox(
                          height: 40,
                        ),
                        const Text(
                          "Enter your username",
                          style: TextStyle(
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        const SizedBox(
                          height: 10,
                        ),
                        _buildEnterEmail(),
                        const SizedBox(
                          height: 20,
                        ),
                        const Text(
                          "Enter your password",
                          style: TextStyle(
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        const SizedBox(
                          height: 10,
                        ),
                        _buildPassword(),
                        const SizedBox(
                          height: 20,
                        ),
                        const Text(
                          "Repeat your password",
                          style: TextStyle(
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        const SizedBox(
                          height: 10,
                        ),
                        _buildRepeatPassword(),
                        const SizedBox(
                          height: 20,
                        ),
                        _buildSignUp(),
                      ],
                    ))))));
  }
}
