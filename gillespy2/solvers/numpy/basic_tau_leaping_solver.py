"""
GillesPy2 is a modeling toolkit for biochemical simulation.
Copyright (C) 2019-2021 GillesPy2 developers.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""

from .tau_leaping_solver import TauLeapingSolver


class BasicTauLeapingSolver(TauLeapingSolver):
    from gillespy2.core import log
    log.warning("The name 'BasicTauLeapingSolver' has been deprecated, future versions of GillesPy2 will not allow"
                " this import. Please import 'TauLeapingSolver'")