import 'package:area/account_page.dart';
import 'package:area/area_tojson.dart';
import 'package:area/choose_action_reaction.dart';
import 'package:area/existing_area_class.dart';
import 'package:flutter/material.dart';
import 'dart:convert';
import 'login_screen.dart';
import 'package:http/http.dart' as http;
import 'end_session.dart';
import 'dart:async';

var areaToJson = AreaToJson();

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

Future<ExistingArea> readJson() async {
  final token = await storage.read(key: 'area-token');
  final response = await http.get(
      Uri.parse('http://10.0.2.2:8080/api/component'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      });
  if (response.statusCode == 200) {
    final data = await json.decode(response.body);
    ExistingArea services = ExistingArea.fromJson(data['data']);
    return (services);
  } else {
    return Future.error("Error when fetching existing AREA");
  }
}

class _HomePageState extends State<HomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false,
        actions: <Widget>[
          IconButton(
            icon: const Icon(
              Icons.account_circle,
              color: Colors.black,
              size: 30,
            ),
            onPressed: () {
              Navigator.pushNamed(
                context,
                AccountPage.routeName,
              ).then((_) => setState(() {}));
            },
          )
        ],
        iconTheme: const IconThemeData(
          color: Colors.black,
        ),
        //automaticallyImplyLeading: false,
        backgroundColor: Colors.white,
        centerTitle: true,
        title: const Text('Welcome to a new AREA !',
            style: TextStyle(color: Colors.black)),
      ),
      backgroundColor: const Color(0xffffffff),
      body: FutureBuilder<ExistingArea>(
          future: readJson(),
          builder: (context, snapshot) {
            if (snapshot.hasError) {
              return const Center(
                child: Text('An error has occurred, please try again later.'),
              );
            } else if (snapshot.hasData) {
              return RenderExistingArea(existingArea: snapshot.data!);
            } else {
              return const Center(
                child: CircularProgressIndicator(),
              );
            }
          }),
    );
  }
}

// ignore: must_be_immutable
class RenderExistingArea extends StatefulWidget {
  RenderExistingArea({Key? key, required this.existingArea}) : super(key: key);

  ExistingArea existingArea;
  bool refreshNeeded = false;
  final fiveSeconds = const Duration(seconds: 5);
  @override
  State<RenderExistingArea> createState() => _RenderExistingAreaState();
}

class _RenderExistingAreaState extends State<RenderExistingArea> {
  Timer? timer;

  @override
  void initState() {
    super.initState();
    timer = Timer.periodic(
        const Duration(seconds: 5),
        (Timer t) => readJson().then((_) => setState(() {
              if (widget.refreshNeeded) {
                build(context);
              }
            })));
  }

  @override
  void dispose() {
    timer?.cancel();
    super.dispose();
  }

  void _checkIfRefreshNeeded(ExistingArea data) {
    int counter = 0;
    while (counter < widget.existingArea.existingItems.length) {
      if (widget.existingArea.existingItems[counter].state !=
          data.existingItems[counter].state) {
        widget.refreshNeeded = true;
        return;
      }
      counter = counter + 1;
    }
    widget.refreshNeeded = false;
    return;
  }

  Future<void> readJson() async {
    final token = await storage.read(key: 'area-token');
    final response = await http.get(
        Uri.parse('http://10.0.2.2:8080/api/component'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
          'authorization': 'Bearer $token',
        });
    if (response.statusCode == 200) {
      final data = await json.decode(response.body);
      ExistingArea checkForRefresh = ExistingArea.fromJson(data['data']);
      _checkIfRefreshNeeded(checkForRefresh);
      widget.existingArea = ExistingArea.fromJson(data['data']);
    } else {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
        content: Text("Error when fetching existing AREA, please try again"),
      ));
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffffffff),
      body: SafeArea(
          child: Padding(
        padding: const EdgeInsets.only(bottom: 60.0),
        child: Center(
          child: Column(
            children: <Widget>[
              const SizedBox(
                height: 5,
              ),
              Expanded(
                child: ListView.builder(
                  itemCount: widget.existingArea.existingItems.length,
                  itemBuilder: _buildExistingArea,
                ),
              ),
            ],
          ),
        ),
      )),
      bottomSheet: createAction(context),
    );
  }

  Future<bool> execDelete(int id) async {
    final token = await storage.read(key: 'area-token');
    final response = await http.delete(
      Uri.parse('http://10.0.2.2:8080/api/component/$id'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      },
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

  Widget _buildExistingArea(BuildContext context, int index) {
    return Dismissible(
      key: UniqueKey(),
      direction: DismissDirection.endToStart,
      onDismissed: (_) async {
        final response =
            await execDelete(widget.existingArea.existingItems[index].id);
        if (response) {
          setState(() {
            widget.existingArea.existingItems.removeAt(index);
          });
        }
      },
      child: Card(
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(20), // if you need this
          side: BorderSide(
            color: Colors.grey.withOpacity(0.3),
            width: 1,
          ),
        ),
        child: InkWell(
          onTap: () {},
          child: ListTile(
            leading: CircleAvatar(
              backgroundColor: Colors.black,
              child: Text(widget.existingArea.existingItems[index].state == true
                  ? "ON"
                  : "OFF"),
            ),
            title: Text(widget.existingArea.existingItems[index].description),
            trailing: const Icon(Icons.arrow_back),
          ),
        ),
      ),
      background: Container(
        margin: const EdgeInsets.symmetric(horizontal: 5),
        alignment: Alignment.centerRight,
        decoration: BoxDecoration(
          borderRadius: BorderRadius.circular(20),
          color: Colors.black,
          boxShadow: const [
            BoxShadow(color: Colors.black, spreadRadius: 0),
          ],
        ),
        child: const Icon(
          Icons.delete,
          color: Colors.white,
        ),
      ),
    );
  }

  Widget createAction(BuildContext context) {
    return SizedBox(
        height: 60,
        width: double.infinity,
        child: ElevatedButton(
            child: const Text(
              'Create new reaction',
              style: TextStyle(
                fontSize: 20,
                fontWeight: FontWeight.bold,
              ),
            ),
            style: ButtonStyle(
              backgroundColor: MaterialStateProperty.all(Colors.black),
              shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                const RoundedRectangleBorder(
                    borderRadius: BorderRadius.zero,
                    side: BorderSide(color: Colors.black)),
              ),
            ),
            onPressed: () async {
              areaToJson.currentAction = null;
              areaToJson.currentReaction = null;
              Navigator.pushNamed(
                context,
                ChooseActionReaction.routeName,
              ).then((_) => setState(() {}));
            }));
  }
}
