import 'package:area/homepage.dart';
import 'package:area/webview_page.dart';
import 'package:http/http.dart' as http;
import './register.dart';
import 'package:flutter/material.dart';
import 'dart:convert';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';

const storage = FlutterSecureStorage();

class LoginScreen extends StatefulWidget {
  const LoginScreen({Key? key}) : super(key: key);

  @override
  State<LoginScreen> createState() => _LoginScreenState();
}

Future<List<String>> fetchOauths() async {
  final response =
      await http.get(Uri.parse('http://10.0.2.2:8080/oauths/create'));

  if (response.statusCode == 200) {
    final data = await json.decode(response.body);
    List<dynamic> list = data['oauths'] as List<dynamic>;
    List<String> oauths = list.cast<String>();
    return oauths;
  } else {
    return Future.error("Failed to load Oauths, please try again");
  }
}

class _LoginScreenState extends State<LoginScreen> {
  final _formKey = GlobalKey<FormState>();
  late String _email;
  late String _password;
  bool _loginError = false;

  bool isEmail(String value) {
    return value.isNotEmpty && value.length >= 2;
  }

  Widget _buildLogo() {
    return Image.asset(
      'images/area_logo.png',
      width: 175,
      height: 175,
    );
  }

  Widget _buildLoginText() {
    return const Text(
      "Login",
      style: TextStyle(
        fontSize: 25,
        fontWeight: FontWeight.bold,
      ),
    );
  }

  Widget _buildEmail() {
    return SizedBox(
        width: 275,
        child: TextFormField(
          validator: (value) =>
              !isEmail(value!) ? "Username not recognize!" : null,
          onSaved: (value) {
            _email = value!;
          },
          decoration: const InputDecoration(
            border: OutlineInputBorder(),
            hintText: 'Enter your username',
          ),
        ));
  }

  Widget _buildPassword() {
    return SizedBox(
        width: 275,
        child: TextFormField(
          obscureText: true,
          validator: (value) => value!.length < 6 ? "Wrong Password!" : null,
          onSaved: (value) {
            _password = value!;
          },
          decoration: const InputDecoration(
            border: OutlineInputBorder(),
            hintText: 'Enter your password',
          ),
        ));
  }

  Future<bool> execLogin() async {
    final response = await http.post(
      Uri.parse('http://10.0.2.2:8080/login'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'username': _email,
        "password": _password,
      }),
    );
    if (response.statusCode == 200) {
      _loginError = false;
      final data = await json.decode(response.body);
      String list = data['token'] as String;
      await storage.write(key: 'area-token', value: list);
      return (true);
    } else {
      _loginError = true;
      return (false);
    }
  }

  Widget _buildLoginButton() {
    return ElevatedButton(
        child: const Text('Login'),
        style: ElevatedButton.styleFrom(
            primary: Colors.black,
            padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 15),
            textStyle:
                const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
        onPressed: () async {
          if (_formKey.currentState!.validate()) {
            final FormState? form = _formKey.currentState;
            form!.save();
            _formKey.currentState?.reset();
            FocusScope.of(context).unfocus();
            final response = await execLogin();
            if (response == true) {
              Navigator.push(
                context,
                PageRouteBuilder(
                  pageBuilder: (c, a1, a2) => const HomePage(),
                  transitionsBuilder: (c, anim, a2, child) =>
                      FadeTransition(opacity: anim, child: child),
                  transitionDuration: const Duration(milliseconds: 250),
                ),
              ).then((value) {});
            }
          }
        });
  }

  Widget _buildSignup() {
    return TextButton(
      onPressed: () {
        _loginError = false;
        Navigator.push(
          context,
          PageRouteBuilder(
            pageBuilder: (c, a1, a2) => const Register(),
            transitionsBuilder: (c, anim, a2, child) =>
                FadeTransition(opacity: anim, child: child),
            transitionDuration: const Duration(milliseconds: 250),
          ),
        );
      },
      style: TextButton.styleFrom(
        primary: Colors.black,
      ),
      child: const Text(
        "SIGN UP",
        style: TextStyle(
          fontSize: 14,
          fontWeight: FontWeight.bold,
          color: Colors.black,
        ),
      ),
    );
  }

  Widget _buildOrLoginWith() {
    return const Text(
      "Or sign in with",
      style: TextStyle(
        fontSize: 14,
        fontWeight: FontWeight.bold,
        color: Colors.black,
      ),
    );
  }

  Widget _buildOauths(List<String> list) {
    return SizedBox(
      height: MediaQuery.of(context).size.height * 0.22,
      child: ListView.builder(
        shrinkWrap: true,
        // ignore: non_constant_identifier_names
        itemBuilder: (ctxt, Index) => _buildOauthsItem(ctxt, Index, list),
        itemCount: list.length,
      ),
    );
  }

  void _handleWebview(BuildContext context, String url, String title) {
    Navigator.push(
        context,
        MaterialPageRoute(
            builder: (context) => WebViewPage(
                  url: url,
                  title: title,
                  comeFrom: false,
                )));
  }

  Widget _buildOauthsItem(BuildContext context, int index, List<String> list) {
    return SizedBox(
        height: 38,
        child: TextButton(
          onPressed: () async {
            final response = await http.get(
                Uri.parse('http://10.0.2.2:8080/auth/link/' + list[index]));

            if (response.statusCode == 200) {
              final data = await json.decode(response.body);
              String url = data['message'] as String;
              _handleWebview(context, url, list[index]);
            } else {
              throw Exception('Failed to load oauths');
            }
          },
          style: TextButton.styleFrom(
            primary: Colors.black,
          ),
          child: Text(
            list[index],
            style: const TextStyle(
              fontSize: 14,
              fontWeight: FontWeight.bold,
              color: Colors.black,
            ),
          ),
        ));
  }

  Widget _buildLoginError() {
    return const Text(
      "Bad credentials, please try again.",
      style: TextStyle(
        fontSize: 14,
        fontWeight: FontWeight.bold,
        color: Colors.red,
      ),
    );
  }

  void checkToken() async {
    final token = await storage.read(key: 'area_token');
    if (token != null) {
      Navigator.push(
        context,
        PageRouteBuilder(
          pageBuilder: (c, a1, a2) => const HomePage(),
          transitionsBuilder: (c, anim, a2, child) =>
              FadeTransition(opacity: anim, child: child),
          transitionDuration: const Duration(milliseconds: 250),
        ),
      ).then((value) {});
    }
  }

  @override
  void initState() {
    super.initState();
    checkToken();
  }

  @override
  Widget build(BuildContext context) {
    return WillPopScope(
        onWillPop: () async => false,
        child: Scaffold(
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
                            const SizedBox(
                              height: 25,
                            ),
                            _buildLogo(),
                            const SizedBox(
                              height: 35,
                            ),
                            _buildLoginText(),
                            const SizedBox(
                              height: 10,
                            ),
                            if (_loginError) _buildLoginError(),
                            _buildEmail(),
                            const SizedBox(
                              height: 10,
                            ),
                            _buildPassword(),
                            const SizedBox(
                              height: 15,
                            ),
                            _buildLoginButton(),
                            const SizedBox(
                              height: 10,
                            ),
                            _buildSignup(),
                            const SizedBox(
                              height: 10,
                            ),
                            _buildOrLoginWith(),
                            const SizedBox(
                              height: 15,
                            ),
                            FutureBuilder<List<String>>(
                              future: fetchOauths(),
                              builder: (context, snapshot) {
                                if (snapshot.hasData) {
                                  return _buildOauths(snapshot.data!);
                                } else if (snapshot.hasError) {
                                  return Text('${snapshot.error}');
                                }
                                return const CircularProgressIndicator();
                              },
                            ),
                          ],
                        )))))));
  }
}
