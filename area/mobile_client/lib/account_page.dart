import 'package:flutter/material.dart';
import 'dart:convert';
import 'login_screen.dart';
import 'package:http/http.dart' as http;
import 'package:area/webview_page.dart';
import 'end_session.dart';

class AccountPage extends StatefulWidget {
  const AccountPage({Key? key}) : super(key: key);
  static const routeName = '/AccountPage';

  @override
  State<AccountPage> createState() => _AccountPageState();
}

class _AccountPageState extends State<AccountPage> {
  List<String> _activeOauth = [];
  final _formKey = GlobalKey<FormState>();
  final _passwordController = TextEditingController();
  late String _password;
  String _username = "";

  _AccountPageState() {
    fetchUsername().then((val) => setState(() {
          _username = val;
        }));
  }
  @override
  void initState() {
    super.initState();
    getActiveOauths();
  }

  void getActiveOauths() async {
    final token = await storage.read(key: 'area-token');
    final response = await http.get(
      Uri.parse('http://10.0.2.2:8080/me'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      },
    );
    if (response.statusCode == 200) {
      final data = await json.decode(response.body);
      List<dynamic> list = data['oauths'] as List<dynamic>;
      _activeOauth = list.cast<String>();
      _username = data['username'];
    } else {
      Navigator.pop(context);
    }
  }

  Widget _buildOauths(List<String> list) {
    return SizedBox(
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
                  comeFrom: true,
                ))).then((_) => setState(() {
          getActiveOauths();
        }));
  }

  Future<void> _handleCoDis(int index, List<String> list) async {
    if (!_activeOauth.contains(list[index])) {
      final response = await http
          .get(Uri.parse('http://10.0.2.2:8080/auth/link/' + list[index]));
      if (response.statusCode == 200) {
        final data = await json.decode(response.body);
        String url = data['message'] as String;
        _handleWebview(context, url, list[index]);
        getActiveOauths();
      } else {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
          content: Text("An error occured, please try again"),
        ));
      }
    } else {
      final token = await storage.read(key: 'area-token');
      final response = await http.put(
        Uri.parse('http://10.0.2.2:8080/disconnect/' + list[index]),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
          'authorization': 'Bearer $token',
        },
      );
      if (response.statusCode == 200) {
        getActiveOauths();
        setState(() {});
        String serviceName = list[index];
        ScaffoldMessenger.of(context).showSnackBar(SnackBar(
          content: Text("$serviceName disconnected"),
        ));
      } else {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
          content: Text("An error occured, please try again"),
        ));
      }
    }
  }

  Widget _buildOauthsItem(BuildContext context, int index, List<String> list) {
    return Container(
        margin: const EdgeInsets.all(5),
        height: 50,
        child: ElevatedButton(
          onPressed: () async {
            await _handleCoDis(index, list);
          },
          style: ElevatedButton.styleFrom(
              primary: _activeOauth.contains(list[index])
                  ? Colors.white
                  : Colors.black,
              padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 15),
              textStyle:
                  const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
          child: Text(
            _activeOauth.contains(list[index])
                ? list[index] + " connected"
                : "Tap to connect with " + list[index],
            style: TextStyle(
              fontSize: 14,
              fontWeight: FontWeight.bold,
              color: _activeOauth.contains(list[index])
                  ? Colors.black
                  : Colors.white,
            ),
          ),
        ));
  }

  Future<List<String>> fetchOauthsAccount() async {
    final response = await http.get(Uri.parse('http://10.0.2.2:8080/oauths/'));

    if (response.statusCode == 200) {
      final data = await json.decode(response.body);
      List<dynamic> list = data['oauths'] as List<dynamic>;
      List<String> oauths = list.cast<String>();
      return oauths;
    } else {
      return Future.error("Failed to load Oauths");
    }
  }

  Widget _buildConnectWithTxt() {
    return const Text(
      "Connect with",
      style: TextStyle(
        fontSize: 25,
        fontWeight: FontWeight.bold,
        color: Colors.black,
      ),
    );
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

  Future<bool> execChangePassword() async {
    final token = await storage.read(key: 'area-token');
    final response = await http.put(
      Uri.parse('http://10.0.2.2:8080/password'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      },
      body: jsonEncode(<String, String>{
        "password": _password,
      }),
    );
    if (response.statusCode == 200) {
      return (true);
    } else if (response.statusCode == 403) {
      EndSession(context);
      return (false);
    } else {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
        content: Text("An error occured, please try again"),
      ));
      return (false);
    }
  }

  Widget _buildChangePasswordButton() {
    return ElevatedButton(
        child: const Text('Change Password'),
        style: ElevatedButton.styleFrom(
            primary: Colors.black,
            padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 15),
            textStyle:
                const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
        onPressed: () async {
          if (_formKey.currentState!.validate()) {
            final FormState? form = _formKey.currentState;
            form!.save();
            final response = await execChangePassword();
            if (response) {
              ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
                content: Text("Your password has been successfully changed"),
              ));
            }
            _formKey.currentState?.reset();
            FocusScope.of(context).unfocus();
          }
        });
  }

  Widget _buildChangePassword() {
    return Column(
      children: <Widget>[
        const SizedBox(
          height: 25,
        ),
        Padding(
          padding: const EdgeInsets.symmetric(horizontal: 10.0),
          child: Container(
            height: 1.0,
            width: 300.0,
            color: Colors.black,
          ),
        ),
        const SizedBox(
          height: 15,
        ),
        const Text(
          "Change Password",
          style: TextStyle(
            fontSize: 25,
            fontWeight: FontWeight.bold,
            color: Colors.black,
          ),
        ),
        const SizedBox(
          height: 25,
        ),
        _buildPassword(),
        const SizedBox(
          height: 15,
        ),
        _buildRepeatPassword(),
        const SizedBox(
          height: 15,
        ),
        _buildChangePasswordButton(),
      ],
    );
  }

  Future<String> fetchUsername() async {
    final token = await storage.read(key: 'area-token');
    final response = await http.get(
      Uri.parse('http://10.0.2.2:8080/me'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      },
    );
    if (response.statusCode == 200) {
      final data = await json.decode(response.body);
      _username = data['username'];
      return (_username);
    } else {
      return ("Enable to find username");
    }
  }

  Widget _buildUsername() {
    return Text(
      "Welcome " + _username,
      style: const TextStyle(
        fontSize: 25,
        fontWeight: FontWeight.bold,
        color: Colors.black,
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          iconTheme: const IconThemeData(
            color: Colors.black, //change your color here
          ),
          backgroundColor: Colors.white,
          centerTitle: true,
          title: const Text('Account',
              style:
                  TextStyle(color: Colors.black, fontWeight: FontWeight.bold)),
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
                        const SizedBox(
                          height: 15,
                        ),
                        _buildUsername(),
                        const SizedBox(
                          height: 15,
                        ),
                        Padding(
                          padding: const EdgeInsets.symmetric(horizontal: 10.0),
                          child: Container(
                            height: 1.0,
                            width: 300.0,
                            color: Colors.black,
                          ),
                        ),
                        const SizedBox(
                          height: 15,
                        ),
                        _buildConnectWithTxt(),
                        const SizedBox(
                          height: 15,
                        ),
                        SizedBox(
                            height: 250,
                            width: 300,
                            child: FutureBuilder<List<String>>(
                              future: fetchOauthsAccount(),
                              builder: (context, snapshot) {
                                if (snapshot.hasData) {
                                  return _buildOauths(snapshot.data!);
                                } else if (snapshot.hasError) {
                                  return Text('${snapshot.error}');
                                }
                                return const CircularProgressIndicator();
                              },
                            )),
                        _buildChangePassword(),
                      ],
                    ))))));
  }
}
