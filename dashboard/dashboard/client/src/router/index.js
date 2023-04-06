import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
import LoginPage from '../views/Login'
import RegisterPage from '../views/Register'
import Dashboard from '../views/Dashboard'
import Profile from '../views/Profile'
import About from '../views/About'
import Confirm from '../views/ConfirmToken'
import Callback from '../views/Callback'
import Forgot from '../views/Forgot'
import Reset from '../views/Reset'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/login',
    name: 'Login',
    component: LoginPage
  },
  {
    path: '/register',
    name: 'Register',
    component: RegisterPage
  },
  {
    path: '/dashboard',
    name: 'Dashboard',
    component: Dashboard
  },
  {
    path: '/profile',
    name: 'Profile',
    component: Profile
  }, {
    path: '/about',
    name: 'About',
    component: About
  }, {
    path: '/confirm',
    name: 'confirm',
    component: Confirm
  }, {
    path: '/callback/:id',
    name: 'callback',
    component: Callback
  }, {
    path: '/forgotPassword',
    name: 'forgotPassword',
    component: Forgot
  }, {
    path: '/reset',
    name: 'reset',
    component: Reset
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

router.beforeEach((to, from, next) => {
  const publicPages = ['/login', '/register', '/', '/confirm', '/forgotPassword', '/reset']
  const authRequired = !publicPages.includes(to.path)
  const loggedIn = localStorage.getItem('dashboard-token')

  if (authRequired && !loggedIn && !to.path.includes('/callback')) {
    return next('/login')
  }
  next()
})

export default router
