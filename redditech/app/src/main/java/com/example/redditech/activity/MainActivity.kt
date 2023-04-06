package com.example.redditech.activity

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.*
import androidx.appcompat.app.ActionBarDrawerToggle
import androidx.core.view.GravityCompat
import androidx.drawerlayout.widget.DrawerLayout
import androidx.fragment.app.Fragment
import com.bumptech.glide.Glide
import com.example.redditech.models.UserInfo
import com.google.android.material.navigation.NavigationView
import android.widget.ImageView
import androidx.annotation.RequiresApi
import androidx.core.content.ContextCompat
import com.example.redditech.controllers.AccountPatch
import com.example.redditech.models.AccountSettings
import com.google.android.material.button.MaterialButton
import androidx.appcompat.widget.SearchView
import com.example.redditech.R
import com.example.redditech.controllers.SearchController
import com.example.redditech.fragments.HomeFragment
import com.example.redditech.fragments.ProfileFragment
import com.example.redditech.fragments.SearchFragment
import com.example.redditech.fragments.SettingsFragment
import com.example.redditech.models.JSONRedditFormatter
import com.example.redditech.models.SearchModel

class MainActivity : AppCompatActivity(), NavigationView.OnNavigationItemSelectedListener {

    private lateinit var toggle : ActionBarDrawerToggle
    private lateinit var drawerLayout: DrawerLayout
    @SuppressLint("SetTextI18n")
    @RequiresApi(Build.VERSION_CODES.O)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val logoutButton = findViewById<Button>(R.id.logout_button)

        logoutButton.setOnClickListener {
            logout()
        }

        drawerLayout = findViewById(R.id.drawer_layout)
        val navView : NavigationView = findViewById(R.id.nav_view)

        toggle = ActionBarDrawerToggle(this, drawerLayout, R.string.open, R.string.close)
        drawerLayout.addDrawerListener(toggle)
        toggle.syncState()
        
        val headView : View = navView.getHeaderView(0)
        val usernameNav : TextView = headView.findViewById(R.id.navUsername)
        val connectedButt : MaterialButton = headView.findViewById(R.id.isOnlineButton)

        initConnectedButt(connectedButt)
        connectedButt.setOnClickListener {
            if (AccountSettings.getProperty("show_presence").toBoolean()) {
                AccountSettings.setProperty("show_presence", "false")
                AccountPatch.showPresence(false)
                connectedButt.text = "Online Status: Off"
                connectedButt.setTextColor(ContextCompat.getColor(this, R.color.dark_grey))
                connectedButt.setStrokeColorResource(R.color.dark_grey)
            } else if (!(AccountSettings.getProperty("show_presence").toBoolean())) {
                AccountSettings.setProperty("show_presence", "true")
                AccountPatch.showPresence(true)
                connectedButt.text = "Online Status: On"
                connectedButt.setTextColor(ContextCompat.getColor(this, R.color.algae_green))
                connectedButt.setStrokeColorResource(R.color.algae_green)
            }
        }
        val usernameCatch = UserInfo.getProperty("display_name")
        if (usernameCatch != null)
            usernameNav.text = usernameCatch
        val imageNav : ImageView = headView.findViewById(R.id.navProfileImage)
        val url = UserInfo.getProfilePicture()
        Glide.with(this)
            .load(url)
            .override(150, 150)
            .fitCenter()
            .into(imageNav)
        navView.setNavigationItemSelectedListener(this)
        supportActionBar?.setDisplayHomeAsUpEnabled(true)
    }

    @SuppressLint("SetTextI18n")
    @RequiresApi(Build.VERSION_CODES.O)
    private fun initConnectedButt(connectedButt: MaterialButton) {
        if (UserInfo.getProperty("show_presence").toBoolean()) {
            connectedButt.text = "Online Status: Off"
            connectedButt.setTextColor(ContextCompat.getColor(this, R.color.dark_grey))
            connectedButt.setStrokeColorResource(R.color.dark_grey)
        } else if (!(UserInfo.getProperty("show_presence").toBoolean())) {
            connectedButt.text = "Online Status: On"
            connectedButt.setTextColor(ContextCompat.getColor(this, R.color.algae_green))
            connectedButt.setStrokeColorResource(R.color.algae_green)
        }
    }

    fun replaceFragment(fragment: Fragment, title : String) {
        val fragmentManager = supportFragmentManager
        val fragmentTransaction = fragmentManager.beginTransaction()
        fragmentTransaction.replace(R.id.main_fragment, fragment)
        fragmentTransaction.commit()
        drawerLayout.closeDrawer(GravityCompat.START)
        supportActionBar?.title = title
    }

    override fun onNavigationItemSelected (item: MenuItem): Boolean {
        val navView : NavigationView = findViewById(R.id.nav_view)
        val m: Menu = navView.menu
        for (i in 0 until m.size()) {
            val mi = m.getItem(i)
            if (mi.itemId != item.itemId) {
                mi.isCheckable = false
            }
        }
        item.isCheckable = true
        item.isChecked = true

        when (item.itemId) {
            R.id.nav_home -> {
                replaceFragment(HomeFragment(), item.title.toString())
            }
            R.id.nav_profile -> {
                replaceFragment(ProfileFragment(), item.title.toString())
            }
            R.id.nav_settings -> {
                replaceFragment(SettingsFragment(), item.title.toString())
            }
        }
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (toggle.onOptionsItemSelected(item)) {
            return true
        }
        return super.onOptionsItemSelected(item)
    }
    fun logout() {
        val p : SharedPreferences = getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
        p.edit().putString("TOKEN", null).apply()
        val intent = Intent(this, LoginActivity::class.java)
        startActivity(intent)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        val inflater = menuInflater
        inflater.inflate(R.menu.search_menu, menu)
        val search = menu?.findItem(R.id.search)
        val searchView = search?.actionView as SearchView
        val mCloseButton : ImageView = searchView.findViewById(androidx.appcompat.R.id.search_close_btn)
        searchView.queryHint = "Search for subreddit"
        searchView.setOnQueryTextListener(object : SearchView.OnQueryTextListener{
            override fun onQueryTextSubmit(query: String?): Boolean {
                SearchController.searchSubreddit(query!!)
                JSONRedditFormatter.formatSubRedditJSON(SearchModel.getData())
                replaceFragment(SearchFragment(), "Search results")
                searchView.setQuery("", false)
                searchView.clearFocus()
                mCloseButton.performClick()
                mCloseButton.performClick()
                return false
            }

            override fun onQueryTextChange(newText: String?): Boolean {
                return false
            }

        })
        return true
    }
}